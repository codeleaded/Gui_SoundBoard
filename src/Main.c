#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/SoundBoard.h"

double FrequencyOutput = 220.0;

double SoundBoard_Function(double t){
	double out = 0.9 * sin(FrequencyOutput * 2.0 * F64_PI * t);
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
	
	if(Stroke(ALX_KEY_Q).PRESSED){
		FrequencyOutput = OctaveBaseFrequency * pow(Root12thOf2,0);
		SoundBoard_Node(&sb,1);
	}else if(Stroke(ALX_KEY_W).PRESSED){
		FrequencyOutput = OctaveBaseFrequency * pow(Root12thOf2,1);	
		SoundBoard_Node(&sb,1);
	}else if(Stroke(ALX_KEY_E).PRESSED){
		FrequencyOutput = OctaveBaseFrequency * pow(Root12thOf2,2);	
		SoundBoard_Node(&sb,1);
	}else if(Stroke(ALX_KEY_R).PRESSED){
		FrequencyOutput = OctaveBaseFrequency * pow(Root12thOf2,3);	
		SoundBoard_Node(&sb,1);
	}else if(Stroke(ALX_KEY_T).PRESSED){
		FrequencyOutput = OctaveBaseFrequency * pow(Root12thOf2,4);	
		SoundBoard_Node(&sb,1);
	}else if(Stroke(ALX_KEY_Z).PRESSED){
		FrequencyOutput = OctaveBaseFrequency * pow(Root12thOf2,5);	
		SoundBoard_Node(&sb,1);
	}else if(Stroke(ALX_KEY_U).PRESSED){
		FrequencyOutput = OctaveBaseFrequency * pow(Root12thOf2,6);	
		SoundBoard_Node(&sb,1);
	}else if(Stroke(ALX_KEY_I).PRESSED){
		FrequencyOutput = OctaveBaseFrequency * pow(Root12thOf2,7);	
		SoundBoard_Node(&sb,1);
	}else if(Stroke(ALX_KEY_O).PRESSED){
		FrequencyOutput = OctaveBaseFrequency * pow(Root12thOf2,8);	
		SoundBoard_Node(&sb,1);
	}else if(Stroke(ALX_KEY_P).PRESSED){
		FrequencyOutput = OctaveBaseFrequency * pow(Root12thOf2,9);	
		SoundBoard_Node(&sb,1);
	}
	
	if(
		Stroke(ALX_KEY_Q).RELEASED || Stroke(ALX_KEY_W).RELEASED ||
		Stroke(ALX_KEY_E).RELEASED || Stroke(ALX_KEY_R).RELEASED ||
		Stroke(ALX_KEY_T).RELEASED || Stroke(ALX_KEY_Z).RELEASED ||
		Stroke(ALX_KEY_U).RELEASED || Stroke(ALX_KEY_I).RELEASED ||
		Stroke(ALX_KEY_O).RELEASED || Stroke(ALX_KEY_P).RELEASED
	){
		FrequencyOutput = 0.0;	
		SoundBoard_Node(&sb,SOUNDBOARD_NONODE);
	}					
	
	Clear(BLACK);

	// String str = String_Format("P: X: %f, Y: %f",p.x,p.y);
	// RenderCStrSize(str.Memory,str.size,0.0f,0.0f,WHITE);
	// String_Free(&str);
}

void Delete(AlxWindow* w){
	SoundBoard_Free(&sb);
}

int main(){
    if(Create("SoundBoard",2500,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}