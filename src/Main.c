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
	
	if(Stroke(ALX_KEY_Q).DOWN){
		SoundBoard_Node(&sb,1,OctaveBaseFrequency * pow(Root12thOf2,0));
	}else if(Stroke(ALX_KEY_W).DOWN){
		SoundBoard_Node(&sb,1,OctaveBaseFrequency * pow(Root12thOf2,1));
	}else if(Stroke(ALX_KEY_E).DOWN){
		SoundBoard_Node(&sb,1,OctaveBaseFrequency * pow(Root12thOf2,2));
	}else if(Stroke(ALX_KEY_R).DOWN){
		SoundBoard_Node(&sb,1,OctaveBaseFrequency * pow(Root12thOf2,3));
	}else if(Stroke(ALX_KEY_T).DOWN){
		SoundBoard_Node(&sb,1,OctaveBaseFrequency * pow(Root12thOf2,4));
	}else if(Stroke(ALX_KEY_Z).DOWN){
		SoundBoard_Node(&sb,1,OctaveBaseFrequency * pow(Root12thOf2,5));
	}else if(Stroke(ALX_KEY_U).DOWN){
		SoundBoard_Node(&sb,1,OctaveBaseFrequency * pow(Root12thOf2,6));
	}else if(Stroke(ALX_KEY_I).DOWN){
		SoundBoard_Node(&sb,1,OctaveBaseFrequency * pow(Root12thOf2,7));
	}else if(Stroke(ALX_KEY_O).DOWN){
		SoundBoard_Node(&sb,1,OctaveBaseFrequency * pow(Root12thOf2,8));
	}else if(Stroke(ALX_KEY_P).DOWN){
		SoundBoard_Node(&sb,1,OctaveBaseFrequency * pow(Root12thOf2,9));
	}else{
		SoundBoard_Node(&sb,SOUNDBOARD_NONODE,sb.freq);
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