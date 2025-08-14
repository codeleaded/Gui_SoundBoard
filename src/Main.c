#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/SoundBoard.h"


double SoundBoard_Function(double t,double f){
	double out = 0.5 * sin(f * 2.0 * F64_PI * t);
	//double out = 0.5 * sin((FrequencyOutput * 2.0 * F64_PI * fmod(t,FrequencyOutput * 2.0 * F64_PI)));
	return out;
	//if(out>0.0f)	return 0.5;
	//else 			return -0.5;
}

SoundBoard sb;

void Setup(AlxWindow* w){
	sb = SoundBoard_New(2,SOUNDBOARD_BITS_PER_SAMPLE,SOUNDBOARD_SAMPLE_RATE);

	SoundBoard_SetFunction(&sb,0,SoundBoard_Function);
	SoundBoard_SetFunction(&sb,1,SoundBoard_Function);
	
	short buffer[1024 * 2];
    memset(buffer,0,sizeof(buffer));
    
	SoundBoard_Set(&sb,buffer,1024);
	SoundBoard_Start(&sb);
}

void Update(AlxWindow* w){
	double OctaveBaseFrequency = 110.0;
	double Root12thOf2 = pow(2.0,1.0 / 12.0);
	
	int SoundBoard_Strokes[] = {
		ALX_KEY_Q,ALX_KEY_W,ALX_KEY_E,ALX_KEY_R,ALX_KEY_T,ALX_KEY_Z,ALX_KEY_U,ALX_KEY_I,ALX_KEY_O,ALX_KEY_P,
		ALX_KEY_A,ALX_KEY_S,ALX_KEY_D,ALX_KEY_F,ALX_KEY_G,ALX_KEY_H,ALX_KEY_J,ALX_KEY_K,ALX_KEY_L,
		ALX_KEY_Y,ALX_KEY_X,ALX_KEY_C,ALX_KEY_V,ALX_KEY_B,ALX_KEY_N,ALX_KEY_M
	};

	char setter = 0;
	for(int i = 0;i<26;i++){
		if(Stroke(SoundBoard_Strokes[i]).DOWN){
			SoundBoard_Node(&sb,1 + i,OctaveBaseFrequency * pow(Root12thOf2,i));
			setter = 1;
		}
	}
	if(!setter) SoundBoard_Node(&sb,0,sb.freq);

	Clear(BLACK);


	const int x = 150;
	const int y = 200;
	const int width = 150;
	const int height = 300;

	for(int i = 1;i<=26;i++){
		float xpos = x;
		float ypos = y;
		if(i<=10) 		xpos += i * width;
		else if(i<=19){
			xpos += (i - 10) * width;
			ypos += height;
		}else{
			xpos += (i - 19) * width;
			ypos += height << 1;
		}

		RenderRect(xpos,ypos,width - 5,height - 5,i == sb.node ? GRAY : WHITE);

		String str = String_Format("%d",i);
		RenderCStrSize(str.Memory,str.size,xpos + ((width - GetAlxFont()->CharSizeX) >> 1),ypos + ((height - GetAlxFont()->CharSizeY) >> 1),WHITE);
		String_Free(&str);
	}
}

void Delete(AlxWindow* w){
	SoundBoard_Free(&sb);
}

int main(){
    if(Create("SoundBoard",2500,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}