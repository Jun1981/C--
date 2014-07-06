/************************************
*                                  *
*    �V���[�e�B���O�Q�[�����[�v    *
*                                  *
************************************
*/

//------ �C���N���[�h�t�@�C���̓ǂݍ��� ------//
#include "../../DxLib/DxLib.h"
#include<windows.h>


//------ �֐��̃v���g�^�C�v�錾 ------//
void key_check();           // �L�[���擾
void game_main();           // �Q�[���R���g���[�����C��
void init();                // �Q�[���V�X�e��������

//------ �ϐ��̒�` ------//
int key_trg, Key_Info, Key_Old;   // �L�[���
int ChkKAny;                             // �Ƃɂ����L�[�������ꂽ��true
int GLpCnt;                             // �Q�[�����[�v�J�E���^

int i, j;//���[�v�p

//�L�����摜�̃f�[�^
int chr[10];//�L�����N�^�[�����摜�ǂݍ��ݗp�ϐ�
int tm[2];//�e�f�[�^�ǂݍ��ݗp�ϐ�

int lx;//�L�����N�^���̒���
int ly;//�L�����N�^�c�̒���


int G_mode;//�Q�[�����[�h�؂�ւ��p
int T_Cnt;//�^�C�g���̂o�t�r�g�@�r�o�`�b�d�_�ŗp

int migihaji;//�E�[�̂����W������ϐ�

int hidarihaji;//���[�̂����W�������ϐ�
int stop;//�[�ɍs���������Ă�t���O


int FontHandle1;//�^�C�g���p�t�H���g�n���h��;//�t�H���g�n���h���P�p
int FontHandle2;//�Q�[���p�t�H���g�n���h��;//�t�H���g�n���h���Q�p


int title;//�^�C�g���摜�ǂݍ��ݗp
int bg; //�Q�[���{�Ҕw�i�摜�p



struct par{

	int x;//x���W
	int y;//y���W
	int sp;//�X�s�[�h
	int dead;//����ł邩�ǂ���

	int life;//�c�莩�@
	int count;//�J�E���^

	int haji;//�[�ɍs�������ǂ����t���O
	int count_MAX;//�J�E���^�ő�l

	int shot;//�e���o�����ǂ���


};//�e�L�����̃p�����[�^


struct par teki[3][2][11];///�G�̍\���̐錾�i�����A���i�ڂ��A����ځj	

struct score{
	int now;//���݃X�R�A
	int high;//�n�C�X�R�A
}ten = { 0, 0 };

struct par jiki;//���@�̍\���̐錾
struct par tama;//���˂����e




/**********************
*    Main program    *
**********************
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);                     // �E�C���h�E���[�h�ɕύX(�������A�Q�T�U�F)

	if (DxLib_Init() == -1) {                    // �c�w���C�u��������������
		return -1;                              // �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);              // �`���𗠉�ʂ�

	init();                                     // �Q�[���V�X�e��������

	//------ �Q�[�����[�v ------//
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) { // Esc�L�[���������܂Ń��[�v
		ClsDrawScreen();                        // ����ʃN���A

		key_check();                            // �L�[���擾
		game_main();                            // �Q�[���R���g���[�����C��
		GLpCnt++;                               // �Q�[�����[�v�J�E���^���v���X

		/////////////////// For debug
		// �t���[���i�Q�[���j�J�E���g�\��
		char b[20];
		wsprintf(b, "%08X", GLpCnt);
		DrawString(500, 32, b, GetColor(255, 255, 255));
		wsprintf(b, "%08X", Key_Info);
		DrawString(500, 52, b, GetColor(255, 255, 255));
		/////////////////// For debug

		ScreenFlip();                           // ����ʂ�\��ʂ�
		if (ProcessMessage() == -1) {            // ���b�Z�[�W����
			break;                              // �G���[���N�����烋�[�v���甲����
		}
	}
	DxLib_End();                                // �c�w���C�u�����g�p�̏I������
	return 0;                                   // �A�v���P�[�V�����̏I��
}


/*-----------------------------
*    �Q�[���V�X�e��������    *
*-----------------------------
*/
void init()
{
	// �Q�[���S�̂Ɋւ��ϐ��̏������A�摜�t�@�C���̓ǂݍ��݂Ȃǂ�����

	LoadDivGraph("../Img/en_my.bmp", 10, 5, 2, 32, 16, chr, 0);//�L�����N�^�ǂݍ���
	LoadDivGraph("../Img/missile.bmp", 2, 2, 1, 2, 16, tm, 0);//�e�摜�̓ǂݍ���
	title = LoadGraph("../Img/title.bmp");//�^�C�g���摜�ǂݍ���
	bg = LoadGraph("../Img/bg.jpg");//�Q�[���{�Ҕw�i�摜

	FontHandle1 = CreateFontToHandle(NULL, 40, 4);//�^�C�g���p�t�H���g�n���h��;//�t�H���g�n���h���P
	FontHandle2 = CreateFontToHandle(NULL, 16, 8);//�Q�[���p�t�H���g�n���h��;//�t�H���g�n���h���Q

	migihaji = 450 + 30;//�L�����N�^�`�ʗ̈�E�[�̂����W
	hidarihaji = 30;//�L�����N�^�`�ʗ̈捶�[�̂����W
	stop = 0;//�G�S�̂��X�g�b�v����

	lx = 32;//�L�����N�^���̒���
	ly = 16;//�L�����N�^�c�̒���

	G_mode = 0;//�Q�[�����[�h
	T_Cnt = 20;//�^�C�g���h�o�t�r�g�@�r�o�`�b�d�h�_�ŗp�J�E���^

	jiki = { 225 + 32, 480 - (16 * 5), 2, 0, { 0 /*tama*/ }, 3, 20 };//���@�̍\���̐錾
	ten.now = 0;//���݃X�R�A�̏�����

	//�e�֌W
	tama.shot = 0;//�e�t���O�O
	tama.sp = 4;//�e�X�s�[�h

	for (i = 0; i < 11; i++)//�G�̏����p�����[�^
	{
		//�G�P�i�΂̈�ԏ�̃��c�@100�_�j
		//teki1[i].x = teki2_1[i].x = teki2_2[i].x = teki3_1[i].x = teki3_2[i].x = (lx - 1) + lx*i;//�G�̂����W
		
		teki[0][0][i].x = (lx - 1) + lx*i;//�΂̓G�̂����W



		teki[0][0][i].y = ly * 5;//�΂̓G�̏��������W
		teki[1][0][i].y = ly * 5 + ly;//���F�̓G�P
		teki[1][1][i].y = ly * 5 + ly*2;//���F�̓G�Q
		teki[2][0][i].y = ly * 5 + ly * 3;//���̓G�P
		teki[2][1][i].y = ly * 5 + ly * 4;//���̓G2



		//teki1[i].y = ly * 5;//�G�̂����W������

		teki[0][0][i].sp = lx / 2;//�G�̈��̈ړ�����
		//teki1[i].sp = teki2_1[i].sp = teki2_2[i].sp = teki3_1[i].sp = teki3_2[i].sp = lx / 2;//�G�̈��ł̈ړ�����

		//teki1[i].dead = teki2_1[i].dead = teki2_2[i].dead = teki3_1[i].dead = teki3_2[i].dead = 0;//�G�ɒe�������������ǂ����i�P�œ�����j
		teki[0][0][i].dead  = 0;//�G�ɒe�������������ǂ����i�P�œ�����j

		//teki1[i].count_MAX = 40;//�G�X�s�[�h�J�E���^�̍ő�l
	    teki[0][0][i].count_MAX = 40;//�G�X�s�[�h�J�E���^�̍ő�l

		//teki1[i].count = teki2_1[i].count = teki2_2[i].count = teki3_1[i].count = teki3_2[i].count = teki1[i].count_MAX;//���t���[�������Ɉړ����邩
		teki[0][0][i].count = teki[0][0][i].count_MAX;//

		//teki1[i].haji = teki2_1[i].haji = teki2_2[i].haji = teki3_1[i].haji = teki3_2[i].haji = 3;//�G���[�ɒ��������ǂ����i�P�Œ������j
		teki[0][0][i].haji = 3;//�G���[�ɒ��������ǂ����i�P�Œ������j


	

	}

}


/**********************************
*    �Q�[���R���g���[�����C��    *
**********************************
*/
void game_main()
{
	// �Q�[���̏���������
	switch (G_mode)
	{

	case 0:


		DrawGraph(70, 80, title, TRUE);//�^�C�g���̕\��


		//�X�y�[�X�L�[�������Ă����������
		if (T_Cnt > 10)
		{

			DrawStringToHandle(170, 300, "Push Space Key !", GetColor(0, 219, 255), FontHandle1); //��������ʒ����ɕ\���@
		}
		else if (T_Cnt > 0)
		{

			DrawStringToHandle(170, 300, "Push Space Key !", GetColor(0, 0, 0), FontHandle1); //��������ʒ����ɕ\��
		}
		else if (T_Cnt == 0)
		{
			T_Cnt = 20;
		}

		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			G_mode = 1;//�Q�[���{�҂�
			DeleteFontToHandle(FontHandle1);//�t�H���g�n���h���P���̂Ă�

		}

		T_Cnt--;//�J�E���^������
		break;

	case 1://�Q�[���{��

		//SetFontSize(20);//�t�H���g�̑傫���ݒ�
		//DrawFormatString(80,20,GetColor(100,100,100),"Your Score %d",0);

		DrawGraph(0, 0, bg, TRUE);//�w�i�̕\��
		DrawFormatStringToHandle(64, 20, GetColor(120, 120, 120), FontHandle2, "Your Score %04d", ten.now);//���݃X�R�A�̕\��
		DrawFormatStringToHandle(450 + 32 - 192, 20, GetColor(120, 120, 120), FontHandle2, "Hi-Score %04d", ten.high);//�n�C�X�R�A�̕\��


		//�e�ƓG�̓����蔻��
		if (tama.shot == 1 && teki[0][0][0].dead == 0 && tama.x + 2 >= teki[0][0][0].x+4 && tama.x <= teki[0][0][0].x + 32-4 && tama.y <= teki[0][0][0].y + 16 && tama.y + 16 >= teki[0][0][0].y)
		{
			ten.now += 100;//100�_�v���X
			tama.shot = 0;//�e�t���O�O
			teki[0][0][0].dead = 1;//�G���S
		}
		//�G�̏���
		if (teki[0][0][0].count == 0)
		{
			teki[0][0][0].count = 40;

			if (stop == 0)
			{
				teki[0][0][0].x += teki[0][0][0].sp;//���ړ�
				if ((teki[0][0][0].x + lx + 1 >= migihaji && teki[0][0][0].sp > 0) || (teki[0][0][0].x - 1 <= 30 && teki[0][0][0].sp < 0))//�[�ɍs�������ǂ����`�F�b�N
				{
					stop = 1;
				}
			}
			else if (stop == 1)

			{
				teki[0][0][0].y += lx;
				teki[0][0][0].sp = ~teki[0][0][0].sp + 1;
				stop = 0;
			}
						


		}


		
		if (tama.shot == 1){
			DrawGraph(tama.x, tama.y, tm[0], TRUE);//�e�O�`��
			tama.y -= tama.sp;//�e�̂����W������
		}
		DrawGraph(jiki.x, jiki.y, chr[3], TRUE);//���@�̕\��
		if (teki[0][0][0].dead == 0)
		{

			DrawGraph(teki[0][0][0].x, teki[0][0][0].y, chr[2], TRUE);//�G�P
		}

		
	

		

		teki[0][0][0].count--;



		//if (CheckHitKey(KEY_INPUT_RIGHT) && jiki.x<450)
		//	jiki.x += jiki.sp;//�E��
		//if (CheckHitKey(KEY_INPUT_LEFT) && jiki.x>0 + lx)
		//	jiki.x -= jiki.sp;//����

		//���@�̑���
		if ((Key_Info&0x01) == 0x01 && jiki.x > 31)
			jiki.x -= jiki.sp;//����
		if ((Key_Info&0x02) == 0x02 && jiki.x + lx < 450 + 31)
			jiki.x += jiki.sp;//�E��
		if ((key_trg&0x10) == 0x10 && tama.shot == 0)
		{

			tama.x = jiki.x+15; tama.y = jiki.y;//�e�Ɍ��݂̎��@���W���
			tama.shot = 1;//�e�O�̔���
		}
		if (tama.y < 0)
		{

			tama.shot = 0;//�e�t���O�O
		}

		break;

	case 2:
		break;
	}
}



/*---------------------
*    �L�[���擾    *
*---------------------
*
*    LEFT  = 0000 0001
*    RIGHT = 0000 0010
*    UP    = 0000 0100
*    DOWN  = 0000 1000
*    key_trg�͉������u�Ԃ̏��
*    key_info�͍��̏��
*
*/
void key_check()
{
	key_trg = Key_Info = 0;                                 // �L�[���N���A
	ChkKAny = false;

	if (CheckHitKey(KEY_INPUT_LEFT))   { Key_Info |= 0x01; }
	if (CheckHitKey(KEY_INPUT_RIGHT))  { Key_Info |= 0x02; }
	if (CheckHitKey(KEY_INPUT_UP))     { Key_Info |= 0x04; }
	if (CheckHitKey(KEY_INPUT_DOWN))   { Key_Info |= 0x08; }

	if (CheckHitKey(KEY_INPUT_SPACE))  { Key_Info |= 0x10; }
	if (CheckHitKey(KEY_INPUT_Z))      { Key_Info |= 0x20; }
	if (CheckHitKey(KEY_INPUT_ESCAPE)) { Key_Info |= 0x40; }
	if (CheckHitKeyAll()) { ChkKAny = true; }                    // ���Ɂ[
	key_trg = (Key_Info ^ Key_Old) & Key_Info;          // �L�[�g���K�[���Z�b�g
	Key_Old = Key_Info;                                     // �L�[���Z�[�u
}

