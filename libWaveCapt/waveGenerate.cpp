#include "waveGenerate.h"

#include <string.h>
#include <noise.h>

//--------------------------------------------------------------------------------------------
Generate::Generate()
{
}

//--------------------------------------------------------------------------------------------
Generate::~Generate()
{
}

//--------------------------------------------------------------------------------------------
void Generate::randParam(Param& param)
{
	param.pos_x = (float)rand()/RAND_MAX;
	param.pos_y = (float)rand()/RAND_MAX;
	param.frequency = (float)rand()/RAND_MAX;
	param.cylinder_fre = (float)rand()/RAND_MAX;
	param.cylinder_angle = (float)rand()/RAND_MAX;
	param.cylinder_scale = (float)rand()/RAND_MAX;
}

//--------------------------------------------------------------------------------------------
void Generate::generateQuestion(Question& question, Param* param)
{
	//清空答案空间
	memset(&(question.imageBuf), 0, Question::IMAGE_BUF_LENGTH);

	//随机参数
	Param rndParam;
	if(param==0)
	{
		randParam(rndParam);
		param=&rndParam;
	}

	noise::module::Cylinders cylinder;
	cylinder.SetFrequency(param->cylinder_fre * 5.0 + 1.5);

	noise::module::RotatePoint rotate;
	rotate.SetSourceModule (0, cylinder);
	rotate.SetAngles (90.0, param->cylinder_angle*90.0, 0.0);

	noise::module::Spheres riperJade;
	riperJade.SetFrequency(param->frequency*4.0+3.0);

	noise::module::TranslatePoint translatePoint;
	translatePoint.SetSourceModule(0, riperJade);
	translatePoint.SetXTranslation(param->pos_x*2.0-1.0);
	translatePoint.SetZTranslation(param->pos_y*2.0-1.0);

	noise::module::Add add;
	add.SetSourceModule(0, translatePoint);
	add.SetSourceModule(1, rotate);

	noise::model::Plane planeModel;
	planeModel.SetModule(add);

	double xDelta  = 2.0 / (double)Question::IMAGE_SIZE;
	double zDelta  = 2.0 / (double)Question::IMAGE_SIZE;
	double xCur    = -1.0;
	double zCur    = -1.0;

	for(int z = 0; z < Question::IMAGE_SIZE; z++) 
	{
		xCur = -1.0;
		for(int x = 0; x < Question::IMAGE_SIZE; x++)
		{
			double finalValue = planeModel.GetValue(xCur, zCur);

			unsigned char color = (unsigned char)((finalValue+2.0)*15.0/4.0);
			
			question.imageBuf[(z*Question::IMAGE_SIZE+x)>>1] |= color<<((x&1) ? 0 : 4);

			xCur += xDelta;
		}
		zCur += zDelta;
	}
}


