/**********************
*                    *
*    �Q�[�����[�v    *
*                    *
**********************
*/

#include "../../DxLib/DxLib.h"
#include<windows.h>
#define count_MAX 10



//�֐��̃v���g�^�C�v�錾
void Shokika();//�ŏ��̐��l
void Draw_IMG();//�摜�`��

//�ϐ��Ȃ�

	int i,j;//���[�v�p

	//�L�����摜�̃f�[�^
	int chr[10];//�L�����N�^�[�����摜�ǂݍ��ݗp�ϐ�
	
	int lx=32;//���̒���
	int ly=16;//�c�̒���
	
	int FontHandle1 = CreateFontToHandle( NULL , 40 , 4 ) ;//�^�C�g���p�t�H���g�n���h��
	int FontHandle2=CreateFontToHandle(NULL,16,8);//�Q�[���p�t�H���g�n���h��

	int G_mode=0;//�Q�[�����[�h
	int ct=20;//�J�E���^
	int title=LoadGraph("../Img/title.bmp");//�^�C�g���摜�ǂݍ���
	int bg=LoadGraph("../Img/bg.jpg");//�Q�[���{�Ҕw�i�摜
	

	int migihaji=450+30;//�E�[�̂����W

	int hidarihaji=30;//���[�̂����W
	int stop=0;//�[�ɍs�����Ƃ��̃X�g�b�v
	
	struct par{

		int x;//x���W
		int y;//y���W
		int sp;//�X�s�[�h
		int hit;//�ʂ�����������
		int life;//�c�莩�@
		int count;//�J�E���^
		int haji;//�[�ɍs�������ǂ����t���O



	};//�e�L�����̃p�����[�^

	struct par jiki={225+32,480-(16*5),2,0,3,count_MAX};//���@�̍\���̐錾
	struct par teki1[11],//�G1(�΂P�O�O�_�j�̍\���̐錾
		teki2_1[11],teki2_2[11],//�G2(���F5�O�_�j�̍\���̐錾
	    teki3_1[11],teki3_2[11];//�G3(���P�O�_�j�̍\���̐錾
	
	
	struct score{
		int now;//���݃X�R�A
		int high;//�n�C�X�R�A
	}ten={0,0};
	



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	ChangeWindowMode(TRUE);                     // �E�C���h�E���[�h�ɕύX(�������A�Q�T�U�F)

	if(DxLib_Init() == -1) {                    // �c�w���C�u��������������
		return -1;                             // �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);              // �`���𗠉�ʂ�
	

/*---------------------
*    Main program    *
*---------------------
*/
	


	

	//------ �Q�[�����[�v ------//
	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0) //while-1
	{ // Esc�L�[���������܂Ń��[�v
		ClsDrawScreen();                        // ����ʃN���A

		// �����ɃQ�[���̏����v���O����������
		Shokika();
		switch(G_mode)
		{

		case 0:


			DrawGraph(70,80,title,TRUE);//�^�C�g���̕\��
			SetFontSize(32);// �����̑傫�����w�肷��

			//�X�y�[�X�L�[�������Ă����������
			if(ct>10)
			{

				//DrawFormatString(170, 300, GetColor(0, 219, 255), "Push Space Key !"); //��������ʒ����ɕ\���@
				DrawStringToHandle(170, 300,  "Push Space Key !",GetColor(0, 219, 255),FontHandle1); //��������ʒ����ɕ\���@
			}
			else if (ct>0)
			{  
				//DrawFormatString(170, 300, GetColor(0, 0, 0), "Push Space Key !"); //��������ʒ����ɕ\���@
				DrawStringToHandle(170, 300, "Push Space Key !",GetColor(0, 0, 0), FontHandle1); //��������ʒ����ɕ\��
			}
			else if(ct==0)
			{
				ct=20;
			}

			if(CheckHitKey(KEY_INPUT_SPACE))
			{
				G_mode=1;//�Q�[���{�҂�
				DeleteFontToHandle( FontHandle1 ) ;//�t�H���g�n���h���P���̂Ă�
				

			}

			ct--;//�J�E���^������
			break;

		case 1://�Q�[���{��

			//SetFontSize(20);//�t�H���g�̑傫���ݒ�
			//DrawFormatString(80,20,GetColor(100,100,100),"Your Score %d",0);
			
			Draw_IMG();

			if(teki1[0].count==0)
			{
				teki1[0].count=count_MAX;

				if(stop==0)
				{
					teki1[0].x+=teki1[0].sp;//���ړ�
					if((teki1[0].x+lx>=migihaji && teki1[0].sp>0) ||( teki1[0].x<=0+lx && teki1[0].sp<0) )//�[�ɍs�������ǂ����`�F�b�N
					{
						stop=1;
					}
				}else if(stop==1)

				{
					teki1[0].y+=lx;
					teki1[0].sp=~teki1[0].sp+1;
					stop=0;
				}

				
			}

			teki1[0].count--;



			if(CheckHitKey(KEY_INPUT_RIGHT) && jiki.x<450)
				jiki.x+=jiki.sp;//�E��
			if(CheckHitKey(KEY_INPUT_LEFT) && jiki.x>0+lx)
				jiki.x-=jiki.sp;//����



			break;	
		case 2:
			break;
		}

		ScreenFlip();                           // ����ʂ�\��ʂ�
		if(ProcessMessage() == -1) {            // ���b�Z�[�W����
			break;                              // �G���[���N�����烋�[�v���甲����
		}





	}//while-1

	DxLib_End();                                // �c�w���C�u�����g�p�̏I������
	return 0;                                   // �\�t�g�̏I��
}

void Shokika(){
	
	for(i=0;i<11;i++)//�G�̏����p�����[�^
	{

		teki1[i].x=teki2_1[i].x=teki2_2[i].x=teki3_1[i].x=teki3_2[i].x=lx+lx*i;
		teki1[i].y=ly*5;
		teki1[i].sp=teki2_1[i].sp=teki2_2[i].sp=teki3_1[i].sp=teki3_2[i].sp=lx/2;
		teki1[i].hit=teki2_1[i].hit=teki2_2[i].hit=teki3_1[i].hit=teki3_2[i].hit=0;
		teki1[i].count=teki2_1[i].count=teki2_2[i].count=teki3_1[i].count=teki3_2[i].count=count_MAX;
		teki1[i].haji=teki2_1[i].haji=teki2_2[i].haji=teki3_1[i].haji=teki3_2[i].haji=1;

		
		teki2_1[i].y=ly*5+ly;
		teki2_2[i].y=ly*5+ly*2;
		teki3_1[i].y=ly*5+ly*3;
		teki2_2[i].y=ly*5+ly*4;
		

	}
}


void Draw_IMG(){
	
	        DrawGraph(0,0,bg,TRUE);//�w�i�̕\��
			DrawFormatStringToHandle(64,20,GetColor(120,120,120),FontHandle2,"Your Score %d",ten.now);//���݃X�R�A�̕\��
			DrawFormatStringToHandle(450+32-192,20,GetColor(120,120,120),FontHandle2,"Hi-Score %d",ten.high);//�n�C�X�R�A�̕\��
			DrawGraph(jiki.x,jiki.y,chr[3],TRUE);//���@�̕\��
			DrawGraph(teki1[0].x,teki1[0].y,chr[2],TRUE);//�G�P
}