#include "timeMeasure.h"

TimeMeasure::TimeMeasure()
{
	freq = start = end = before = now = LARGE_INTEGER();
	if (!QueryPerformanceFrequency(&freq))
		assert(0 && "�P�ʏK���Ɏ��s���܂���");
	state = 0;
}

void TimeMeasure::Start()
{
	//���̓���������start�ɑ������֐�
	if (!QueryPerformanceCounter(&start))
		assert(0 && "�J�n���Ԃ̎擾�Ɏ��s���܂���");
	//�X�e�[�g��ς���
	state++;
}

double TimeMeasure::End()
{
	//�X�e�[�g���ς���Ă邩�`�F�b�N����
	if (state != 1)
		assert(0 && "Start�֐����Ă�ł��܂���");

	//���̓���������end�ɑ��
	if (!QueryPerformanceCounter(&end))
		assert(0 && "�I�����Ԃ̎擾�Ɏ��s���܂���");

	//�߂�l�p�̕ϐ�
	double result = 0;

	//start-end�Ōo�ߎ��Ԃ��擾���P�ʎ��ԂŊ��邱�ƂŐ������o�ߎ��Ԃ��擾����
	result = static_cast<double>((end.QuadPart - start.QuadPart) / freq.QuadPart);

	//�X�e�[�g��߂�
	state = 0;

	return result;
}

double TimeMeasure::Lap()
{
	//�X�e�[�g���ς���Ă邩�`�F�b�N����
	switch (state)
	{
	case 0:
		assert(0 && "Start���Ă΂�Ă��܂���");
		break;
	case 1:
		before = start;
		break;
	case 2:
		before = now;
		break;
	default:
		assert(0 && "�s��l�������Ă��܂�");
		break;
	}
	//���̓���������end�ɑ��
	if (!QueryPerformanceCounter(&now))
		assert(0 && "���ݎ��Ԃ̎擾�Ɏ��s���܂���");

	//�߂�l�p�̕ϐ�
	double result = 0;

	//before - now�Ōo�ߎ��Ԃ��擾���P�ʎ��ԂŊ��邱�ƂŐ������o�ߎ��Ԃ��擾����
	result = static_cast<double>((double)(now.QuadPart - before.QuadPart) / freq.QuadPart);

	//�X�e�[�g��ݒ�
	state = 2;

	return result;
}
