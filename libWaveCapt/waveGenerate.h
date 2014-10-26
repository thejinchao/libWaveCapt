#ifndef __LIB_WAVE_CAPTCHA_INCLUDE__
#define __LIB_WAVE_CAPTCHA_INCLUDE__

class Generate
{
public:
	struct Question
	{
		/// 图片尺寸
		enum { IMAGE_SIZE=128 };
		/// 图片需要的内存字节
		enum { IMAGE_BUF_LENGTH = IMAGE_SIZE*IMAGE_SIZE/2 };

		unsigned char imageBuf[IMAGE_BUF_LENGTH];	//!< 图片数据
		
		unsigned char answerRect[4]; //!< 正确答案所在的范围(left, top, right, bottom)
	};

	/** 创建参数
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
	/** 产生一个问题
	*/
	void generateQuestion(Question& question, Param* param=0);
	/** 产生随机参数 */
	void randParam(Param& param);

public:
	Generate();
	~Generate();
};

#endif
