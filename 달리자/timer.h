#pragma once //������ cpp�� 
//QueryPerformanceFrequency, QueryPerformanceCounter ����:http://www.tipssoft.com/bulletin/board.php?bo_table=FAQ&wr_id=735

class timer
{
private:
	bool _isGoodHardware; //���κ��尡 ��ü ���ػ� Ÿ�̸Ӹ� �����ϴ°�? (�ƴϸ� _timeScale = 0.001f�� ����)

	float _timeScale; //cpu�� ��Ŭ�� ���� �ð� (��: 3.6Ghz cpu�� 1�ʴ� 3.6Ghz���� -> ��Ŭ�� �ð� 1��/3.6 * 10^9 (�Ⱑ))
	float _timeElapsed; //����ð� (�� �����Ӵ� ����ð�, ���� fps�� 1/60)

	__int64 _curTime; //�� ���� cpu Ŭ�� �� //Time�̶�� ��Ī�� �������� ����
	__int64 _lastTime; //���� ������� cpu Ŭ�� ��
	__int64 _periodFrequency; //�����ð� ���� �߻��� cpu Ŭ���� (���ļ�)

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	HRESULT init();
	void tick(float lockFPS = 0.0f); 
	//while�� �̿��� �̿��� _lastTime���� 1��/lockFPS �ʰ� ���������� tick�Լ��� �����
	//��: 1��/lockFPS �� �� 1/10 �� �ϰ��, 0�ʿ� update�� ����Ǿ� 0.05�ʿ� update ������ ������ tick �Լ��� ����Ǹ�
	//while �ȿ��� 0.1�ʰ� �ɶ����� ��Ƶ� �� ���� update�� ����ȴ�. => update ������ 0.1�� ���� ª����
	//�׻� 0.1�� �������� update�� ����ȴ�. (update ������ �� �ɸ��� tick�� while���� �ٷ� �������ͼ� update �������� ����)
	
	unsigned long getFrameRate(char* str = NULL) const; //�Լ� ���� ���� const Ű���� : http://felixblog.tistory.com/70 , http://simplesolace.tistory.com/entry/const-���-�Լ�
														//const �Լ��� �ڱⰡ ���� ��ü�� �������� ������ �� ���� �б⸸ �� �� �ִ�.
	
	inline float getElapsedTime() const { return _timeElapsed; }; //inline, template�� �� ���Ͽ� ���� ���� �� �Ǿ�� ��밡��
	inline float getWorldTime() const { return _worldTime; };
	inline int getFrameCount() const { return _FPSFrameCount; }

	timer();
	~timer();
};