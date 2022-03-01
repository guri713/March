#include "timeMeasure.h"

TimeMeasure::TimeMeasure()
{
	freq = start = end = before = now = LARGE_INTEGER();
	if (!QueryPerformanceFrequency(&freq))
		assert(0 && "単位習得に失敗しました");
	state = 0;
}

void TimeMeasure::Start()
{
	//今の内部時刻をstartに代入する関数
	if (!QueryPerformanceCounter(&start))
		assert(0 && "開始時間の取得に失敗しました");
	//ステートを変える
	state++;
}

double TimeMeasure::End()
{
	//ステートが変わってるかチェックする
	if (state != 1)
		assert(0 && "Start関数を呼んでいません");

	//今の内部時刻をendに代入
	if (!QueryPerformanceCounter(&end))
		assert(0 && "終了時間の取得に失敗しました");

	//戻り値用の変数
	double result = 0;

	//start-endで経過時間を取得し単位時間で割ることで正しい経過時間を取得する
	result = static_cast<double>((end.QuadPart - start.QuadPart) / freq.QuadPart);

	//ステートを戻す
	state = 0;

	return result;
}

double TimeMeasure::Lap()
{
	//ステートが変わってるかチェックする
	switch (state)
	{
	case 0:
		assert(0 && "Startが呼ばれていません");
		break;
	case 1:
		before = start;
		break;
	case 2:
		before = now;
		break;
	default:
		assert(0 && "不定値が入っています");
		break;
	}
	//今の内部時刻をendに代入
	if (!QueryPerformanceCounter(&now))
		assert(0 && "現在時間の取得に失敗しました");

	//戻り値用の変数
	double result = 0;

	//before - nowで経過時間を取得し単位時間で割ることで正しい経過時間を取得する
	result = static_cast<double>((double)(now.QuadPart - before.QuadPart) / freq.QuadPart);

	//ステートを設定
	state = 2;

	return result;
}
