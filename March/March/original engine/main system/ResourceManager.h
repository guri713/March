#pragma once

#include <fstream>
#include <d3d11.h>
#include <string>
#include <WICTextureLoader.h>
#include <DirectXTex.h>

inline bool ReadBinaryFile(const char* _filename, char** _blob, unsigned int& _size)
{
	std::ifstream _input_file(_filename, std::ifstream::binary);
	_input_file.seekg(0, std::ifstream::end);
	_size = static_cast<int>(_input_file.tellg());
	_input_file.seekg(0, std::ifstream::beg);
	*_blob = new char[_size];
	_input_file.read(*_blob, _size);
	return true;
}


class ResourceManager
{
private:

	template <class Resource>
	struct sResource
	{
		#pragma region variable
		int i_ref_num;//リファレンスの格納インデックス
		std::wstring path;//リファレンスのファイル名
		Resource resource;
		ID3D11InputLayout* layout;
#pragma endregion

		#pragma region function
		sResource() : i_ref_num(0), resource(nullptr),layout(nullptr) { path[0] = '\0'; }

		void Release(bool _force = false) 
		{
			//インデックスは0以上のはずなので0は例外なので終了
			if (i_ref_num == 0) return;

			//インデックスをインクリメントして0になるとき(0は1文前で処理しているので1の時のみ)
			if (--i_ref_num <= 0) _force = true;

			//forceがtrueの場合はshaderResourceViewを解放する
			if (_force)
			{
				if (typeid(*resource) == typeid(ID3D11VertexShader))
					if (layout)layout->Release();

				if (resource) resource->Release();
				resource = nullptr;
				i_ref_num = 0;
				path[0] = '\0';
			}
		}

#pragma endregion

	};

public:
	enum class e_resource_kind
	{
		SRV,
		Vertex,
		Pixel,
		Compute,
		Geometry,
	};

private:

	//variable(変数)
	static const int resource_max = 256;//リファレンスの上限
	static sResource<ID3D11ShaderResourceView*>	shader_resource_views[resource_max];
	static sResource<ID3D11VertexShader*> vertex_shaders[resource_max];
	static sResource<ID3D11PixelShader*> pixel_shaders[resource_max];
	static sResource<ID3D11ComputeShader*> compute_shaders[resource_max];
	static sResource<ID3D11GeometryShader*> geometry_shaders[resource_max];

	ResourceManager() {}
	~ResourceManager() {}

public:

	static ResourceManager* GetInstance()
	{
		static ResourceManager _instance;

		return &_instance;
	}


	//シェーダーリソースビューのロード

	/// <summary>
	/// ShaderResourceViewのロード
	/// </summary>
	/// <param name="_device"></param>
	/// <param name="_file_name"></param>
	/// <param name="_shader_resource_view"></param>
	/// <param name="_tex_desc"></param>
	/// <param name="_tex2d"></param>
	/// <param name="_use_srgb"></param>
	/// <returns></returns>
	static bool LoadShaderResourceView(ID3D11Device* _device, std::wstring _file_name,
		ID3D11ShaderResourceView** _shader_resource_view, D3D11_TEXTURE2D_DESC* _tex_desc, ID3D11Texture2D* _tex2d, bool _use_srgb = true)

	{
		//フルパスからファイル名のみを切り取ったもの
		std::wstring _only_file_name{};
		//文字列を切り取るために使用
		size_t _slash_start = _file_name.find_last_of('/');
		//文字列を切り取るために使用
		size_t _back_slash_start = _file_name.find_last_of('\\');


		if (_slash_start != std::wstring::npos)
		{
			_only_file_name = _file_name.substr(_slash_start);
		}

		if (_back_slash_start != std::wstring::npos)
		{
			_only_file_name = _file_name.substr(_back_slash_start);
		}

		HRESULT hr = 0;
		int _index = -1;
		sResource<ID3D11ShaderResourceView*>* find = nullptr;
		ID3D11Resource* _resource = nullptr;
		bool _use_SRGB = false;
		//	データ探索
		for (int i = 0; i < resource_max; i++)
		{
			sResource<ID3D11ShaderResourceView*>* stored_resource = &shader_resource_views[i];

			//データがなかったらその領域にデータを作る
			if (stored_resource->i_ref_num == 0)
			{
				//データ作成時のインデックスをセット
				if (_index == -1) _index = i;
				continue;
			}

			//	ファイルパスが違うなら無視
			if (wcscmp(stored_resource->path.c_str(), _file_name.c_str()) != 0) continue;

			//	同名ファイルが存在したらそれを使用する
			find = stored_resource;
			stored_resource->resource->GetResource(&_resource);
			break;
		}

		//	データが見つからなかったので新規読み込み
		if (!find)
		{
			//画像読み込みに必要な変数
			DirectX::TexMetadata _metadata = DirectX::TexMetadata();
			DirectX::ScratchImage _image;

			//拡張子を識別する
			std::wstring _dummy = _only_file_name;
			size_t _start = _dummy.find_last_of(L".");
			std::wstring _extension = _dummy.substr(_start, _dummy.size() - _start);

			//空いているスロットに読み込む
			sResource<ID3D11ShaderResourceView*>* stored_resource = &shader_resource_views[_index];

			//画像をSRGBで読み込むか決める
			int _use_state = DirectX::WIC_LOADER_DEFAULT;
			if (_use_srgb)
				_use_state = DirectX::WIC_LOADER_FORCE_SRGB;

			if (L".png" == _extension)//pngの場合
			{
				if (FAILED(DirectX::CreateWICTextureFromFileEx
				(_device, _file_name.c_str(), 0,
					D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, _use_state,
					&_resource, &(stored_resource->resource))))
					return false;
			}
			else
			{
				if (L".jpeg" == _extension || L".jpg" == _extension || L".jpe" == _extension || L".gif" == _extension || L".tiff" == _extension || L".tif" == _extension || L".bmp" == _extension)
				{
					if (FAILED(DirectX::LoadFromWICFile(_file_name.c_str(), 0, &_metadata, _image)))
						return false;
				}
				else if (L".dds" == _extension || L".DDS" == _extension)
				{
					if (FAILED(DirectX::LoadFromDDSFile(_file_name.c_str(), 0, &_metadata, _image)))
						return false;
				}
				else if (L".tga" == _extension || L".vda" == _extension || L".icb" == _extension || L".vst" == _extension)
				{
					_use_SRGB = true;

					if (FAILED(DirectX::LoadFromTGAFile(_file_name.c_str(), &_metadata, _image)))
						return false;
				}

				hr = DirectX::CreateShaderResourceViewEx
				(_device, _image.GetImages(), _image.GetImageCount(), _metadata, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, D3D11_RESOURCE_MISC_TEXTURECUBE, _use_state, &(stored_resource->resource));
			}
			find = stored_resource;
			stored_resource->path = _file_name;
			stored_resource->resource->GetResource(&_resource);
		}

		//	最終処理
		if (_tex2d != nullptr)
		{
			_resource->QueryInterface(&_tex2d);
			*_shader_resource_view = find->resource;
			_tex2d->GetDesc(_tex_desc);
			find->i_ref_num++;
			_resource->Release();
		}
		else
		{
			ID3D11Texture2D* _tex2d;
			_resource->QueryInterface(&_tex2d);
			*_shader_resource_view = find->resource;
			_tex2d->GetDesc(_tex_desc);
			find->i_ref_num++;
			_tex2d->Release();
			_resource->Release();
		}
		return true;
	}

	/// <summary>
	/// VertexShaderのロード
	/// </summary>
	/// <param name="_device"></param>
	/// <param name="_cso_file_name">ファイル名</param>
	/// <param name="_input_element_desc"></param>
	/// <param name="_num_elements"></param>
	/// <param name="_vertex_shader">ロード先のアドレス</param>
	/// <param name="_input_layout"></param>
	/// <returns></returns>
	static bool LoadVertexShader(
		ID3D11Device* _device, std::string _cso_file_name,
		D3D11_INPUT_ELEMENT_DESC* _input_element_desc, int _num_elements,
		ID3D11VertexShader** _vertex_shader, ID3D11InputLayout** _input_layout)

	{
		*_vertex_shader = nullptr;
		*_input_layout = nullptr;

		sResource<ID3D11VertexShader*>* _find = nullptr;
		int _index = -1;

		std::wstring _filename(_cso_file_name.begin(), _cso_file_name.end());

		//	データ検索
		for (int i = 0; i < resource_max; i++) {
			sResource<ID3D11VertexShader*>* _stored_resource = &vertex_shaders[i];

			if (_stored_resource->i_ref_num == 0) {
				if (_index == -1) _index = i;
				continue;
			}

			if (wcscmp(_stored_resource->path.c_str(), _filename.c_str()) != 0) continue;

			//	同名ファイルが存在した
			_find = _stored_resource;
			break;
		}

		//	データが見つからなかった
		if (!_find) {
			sResource<ID3D11VertexShader*>* _stored_resource = &vertex_shaders[_index];
			char* blob;
			unsigned int size;

			//	コンパイル済みピクセルシェーダーオブジェクトの読み込み
			if (!ReadBinaryFile(_cso_file_name.c_str(), &blob, size)) return false;

			//	頂点シェーダーオブジェクトの生成
			if (FAILED(_device->CreateVertexShader(blob, size, nullptr, &_stored_resource->resource)))
				return false;

			HRESULT hr = _device->CreateInputLayout(_input_element_desc, _num_elements, blob, size, &_stored_resource->layout);
			//	入力レイアウトの作成
			delete[] blob;
			if (FAILED(hr)) return false;

			//	新規データの保存
			_find = _stored_resource;
			_find->path = _filename;
		}

		//	最終処理
		*_vertex_shader = _find->resource;
		*_input_layout = _find->layout;
		_find->i_ref_num++;

		return true;
	}


	/// <summary>
	/// シェーダーのロード関数(Vertex意外)
	/// </summary>
	/// <typeparam name="Shader"></typeparam>
	/// <param name="_cso_file_name">ファイル名</param>
	/// <param name="_shader">ロード先のアドレス</param>
	/// <param name="_kind">シェーダーの種類</param>
	/// <returns></returns>
	template <class Shader>
	static bool LoadShader(ID3D11Device* _device, std::string _cso_file_name, Shader _shader,e_resource_kind _kind)
	{
		void* _stored_resources;
		switch (_kind)
		{
		case e_resource_kind::Pixel:
			_stored_resources = pixel_shaders;
			break;
		case e_resource_kind::Compute:
			_stored_resources = compute_shaders;
			break;
		case e_resource_kind::Geometry:
			_stored_resources = geometry_shaders;
			break;
		default:
			assert(0 && "The unavailable type has been selected.");
			return false;
			break;
		}

		//引数のシェーダーをリセットする
		*_shader = nullptr;
		void* _find = nullptr;
		//データ検索の際に使用
		int _no = -1;

		//char型からw_char型に変換
		std::wstring _filename(_cso_file_name.begin(), _cso_file_name.end());

		//	データ検索
		for (int n = 0; n < resource_max; n++) {
			void* _stored_resource = &_stored_resources[n];
			if (_stored_resource->i_ref_num == 0)
			{
				if (_no == -1) _no = n;
				continue;
			}
			if (wcscmp(p->path.c_str(), _filename.c_str()) != 0) continue;

			//	同名ファイルが存在した
			_find = p;
			break;
		}

		//	新規作成
		if (!_find) 
		{
			void* _stored_resource = &_stored_resources[_no];
			char* blob;
			unsigned int size;

			//	コンパイル済みコンピュートシェーダーオブジェクトの読み込み
			if (!ReadBinaryFile(_cso_file_name.c_str(), &blob, size)) return false;

			HRESULT hr;
			switch (_kind)
			{
			case ResourceManager::e_resource_kind::Pixel:
				hr = _device->CreatePixelShader(blob, size, nullptr, &_stored_resource->resource);
				break;
			case ResourceManager::e_resource_kind::Compute:
				hr = _device->CreateComputeShader(blob, size, nullptr, &_stored_resource->resource);
				break;
			case ResourceManager::e_resource_kind::Geometry:
				hr = _device->CreateGeometryShader(blob, size, nullptr, &_stored_resource->resource);
				break;
			default:
				return false;
				break;
			}
			delete[] blob;
			if (FAILED(hr)) return false;

			_find = _stored_resource;
			_find->path = _filename;
		}

		//	最終処理（参照渡しでデータを渡す）
		*_shader = _find->resource;
		_find->i_ref_num++;

		return true;
	}

	/// <summary>
	/// 全リソースの解放
	/// </summary>
	static void ReleaseAll()
	{
		for (int i = 0; i < resource_max; i++) {
			shader_resource_views[i].Release(true);
			vertex_shaders[i].Release(true);
			pixel_shaders[i].Release(true);
			compute_shaders[i].Release(true);
			geometry_shaders[i].Release(true);
		}
	}

	/// <summary>
	/// 指定のリソースの解放
	/// </summary>
	/// <typeparam name="Resource"></typeparam>
	/// <param name="_resource">リソースのアドレス</param>
	/// <param name="_kind">リソースの種類</param>
	template <class Resource>
	static void Release(Resource* _resource,e_resource_kind _kind)
	{
		if (_resource == nullptr)return;
		
		void* _stored_resources;
		switch (_kind)
		{
		case e_resource_kind::SRV:
			_stored_resources = shader_resource_views;
			break;
		case e_resource_kind::Vertex:
			_stored_resources = vertex_shaders;
			break;
		case e_resource_kind::Pixel:
			_stored_resources = pixel_shaders;
			break;
		case e_resource_kind::Compute:
			_stored_resources = compute_shaders;
			break;
		case e_resource_kind::Geometry:
			_stored_resources = geometry_shaders;
			break;
		}
		for (int _index = 0; _index < resource_max; _index++)
		{
			void* _stored_resource = &_stored_resources[_index];

			if (_stored_resource->i_ref_num == 0) continue;

			if (_resource != _stored_resource->resource) continue;

			//	データが存在した
			_stored_resource->Release();
			break;
		}
	}


};

