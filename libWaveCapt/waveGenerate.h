#ifndef __LIB_WAVE_CAPTCHA_INCLUDE__
#define __LIB_WAVE_CAPTCHA_INCLUDE__

class Generate
{
public:
	struct Question
	{
		/// ͼƬ�ߴ�
		enum { IMAGE_SIZE=128 };
		/// ͼƬ��Ҫ���ڴ��ֽ�
		enum { IMAGE_BUF_LENGTH = IMAGE_SIZE*IMAGE_SIZE/2 };

		unsigned char imageBuf[IMAGE_BUF_LENGTH];	//!< ͼƬ����
		
		unsigned char answerRect[4]; //!< ��ȷ�����ڵķ�Χ(left, top, right, bottom)
	};

	/** ��������
	*/
	struct Param
	{
		float pos_x;
		float pos_y;
		float frequency;
		float cylinder_fre;
		float cylinder_angle;
		float cylinder_scale;
	};

public:
	/** ����һ������
	*/
	void generateQuestion(Question& question, Param* param=0);
	/** ����������� */
	void randParam(Param& param);

public:
	Generate();
	~Generate();
};

#endif
