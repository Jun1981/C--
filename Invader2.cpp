/************************************
*                                  *
*    �V���[�e�B���O�Q�[�����[�v    *
*                                  *
************************************
*/

//TODO

//init �Ł@�S�G�̐ݒ�


//------ �C���N���[�h�t�@�C���̓ǂݍ��� ------//
#include "../../DxLib/DxLib.h"
#include<windows.h>
#include<time.h>
#include <stdlib.h>


//------ �֐��̃v���g�^�C�v�錾 ------//
void key_check();           // �L�[���擾
void game_main();           // �Q�[���R���g���[�����C��
void init();                // �Q�[���V�X�e��������
void haikei();//�w�i�\��

void hyouji_all();//�\���S��
void jiki_hyouji();
void jikidan_hyouji();
void jikidan_idou();
void jiki_tenmetsu();
void teki_hyouji();
void tekidan_hyouji();
void tekidan_idou();
void tekidan_hassha();
void zanki();

void teki_idou();//�G�ړ��֐�

void haji_chk();

void counter();//�J�E���^�֐�
void gover_chk();//�G�������̃��C���ɓ��B������Q�[���I�[�o�[

void teki_atari();//���@�e�ƓG�̓����蔻��֐�
void jiki_atari();//�G�e�Ǝ��@�̓����蔻��֐�
void sentou_chk();//�G�̗�̒��Ő擪���N���`�F�b�N
void teki_nokori_chk();//�G�̎c��`�F�b�N


//------ �ϐ��̒�` ------//
int key_trg, Key_Info, Key_Old;   // �L�[���
int ChkKAny;                             // �Ƃɂ����L�[�������ꂽ��true
int GLpCnt;                             // �Q�[�����[�v�J�E���^

int i, j,k;//���[�v�p

//�L�����摜�̃f�[�^
int title;//�^�C�g���摜�ǂݍ��ݗp
int bg; //�Q�[���{�Ҕw�i�摜�p
int GO;//�Q�[���I�[�o�[��ʓǂݎ��p
int cl;//�N���A��ʗp


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





int rd;//�����_���p�ϐ�
int dead_cnt = 100;//���񂾂Ƃ��̃J�E���^

int en_cnt_MAX = 100;//�G�������[�v���Ƃɓ������ő�l
int en_cnt=en_cnt_MAX;//�G�������[�v���Ƃɓ�����

int haji=0;//�G���[�ɗ����Ƃ��̃t���O

static int alpha;
int fade_mode=0;//�P���t�F�[�h�C���Q���t�F�[�h�A�E�g

int sentou[5][11] = { 0 };

int teki_nokori=55;//�G�̎c��


struct par{

	int x;//x���W
	int y;//y���W
	int sp;//�X�s�[�h
	int t_sp;//�e�X�s�[�h
	int dead;//����ł邩�ǂ���

	int life;//�c�莩�@
	int count;//�J�E���^

	int haji;//�[�ɍs�������ǂ����t���O
	int count_MAX;//�J�E���^�ő�l

	int shot;//�e���o�����ǂ���

	int kankaku;//�G�̒e�����Ԋu
	int kankaku_sk;//�G�̒e�����Ԋu�����l

	int tama_x;
	int tama_y;

	int sentou;//���擪�ɂ��邩�ǂ���

	

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

	//�����_������
	srand((unsigned)time(NULL));

	// �Q�[���S�̂Ɋւ��ϐ��̏������A�摜�t�@�C���̓ǂݍ��݂Ȃǂ�����

	LoadDivGraph("../Img/en_my.png", 10, 5, 2, 32, 16, chr, 0);//�L�����N�^�ǂݍ���
	LoadDivGraph("../Img/missile1.png", 2, 2, 1, 2, 16, tm, 0);//�e�摜�̓ǂݍ���
	title = LoadGraph("../Img/title.bmp");//�^�C�g���摜�ǂݍ���
	bg = LoadGraph("../Img/bg.jpg");//�Q�[���{�Ҕw�i�摜
	GO = LoadGraph("../Img/gover.jpg");//�Q�[���I�[�o�[���
	cl = LoadGraph("../Img/gclear.jpg");//�N���A���
	

	FontHandle1 = CreateFontToHandle(NULL, 40, 4);//�^�C�g���p�t�H���g�n���h��;//�t�H���g�n���h���P
	FontHandle2 = CreateFontToHandle(NULL, 16, 8);//�Q�[���p�t�H���g�n���h��;//�t�H���g�n���h���Q

	migihaji = 450 + 30;//�L�����N�^�`�ʗ̈�E�[�̂����W
	hidarihaji = 30;//�L�����N�^�`�ʗ̈捶�[�̂����W
	stop = 0;//�G�S�̂��X�g�b�v����



	lx = 32;//�L�����N�^���̒���
	ly = 16;//�L�����N�^�c�̒���

	G_mode = 0;//�Q�[�����[�h
	T_Cnt = 20;//�^�C�g���h�o�t�r�g�@�r�o�`�b�d�h�_�ŗp�J�E���^


	jiki.x = 225 + 32; jiki.y = 480 - (16 * 5), jiki.sp = 2; jiki.t_sp = 4; jiki.dead = 0; jiki.life = 3; jiki.shot = 0;//���@�̍\���̐錾
	ten.now = 0;//���݃X�R�A�̏�����

	//�e�֌W
	//tama.shot = 0;//�e�t���O�O
	//tama.sp = 4;//�e�X�s�[�h
	
	

	

	for (k = 0; k < 11; k++){
		teki[0][0][k].y = ly * 5;//�΂̓G�̏��������W
		teki[0][0][k].kankaku_sk = rand() % 100 + 100;//�΂̓G�̒e�����Ԋu
		teki[0][0][k].kankaku = teki[0][0][k].kankaku_sk;
		teki[0][0][k].t_sp = 6;

		teki[1][0][k].y = ly * 7;//���F�P���������W
		teki[1][0][k].kankaku_sk = rand() % 300 + 500;//���F1�G�̒e�����Ԋu
		teki[1][0][k].kankaku = teki[1][0][k].kankaku_sk;
		teki[1][0][k].t_sp = 4;

		teki[1][1][k].y = ly * 9;//���F�Q���������W
		teki[1][1][k].kankaku_sk = rand() % 300 + 500;//���F2�G�̒e�����Ԋu
		teki[1][1][k].kankaku = teki[1][1][k].kankaku_sk;
		teki[1][1][k].t_sp = 4;

		teki[2][0][k].y = ly * 11;//���P���������W
		teki[2][0][k].kankaku_sk = rand() % 300 + 600;//���P�G�̒e�����Ԋu
		teki[2][0][k].kankaku = teki[2][0][k].kankaku_sk;
		teki[2][0][k].t_sp = 3;

		teki[2][1][k].y = ly * 13;//���Q���������W
		teki[2][1][k].kankaku_sk = rand() % 300 + 600;//���Q�G�̒e�����Ԋu
		teki[2][1][k].kankaku = teki[2][1][k].kankaku_sk;
		teki[2][1][k].t_sp = 3;

		for (j = 0; j < 2; j++){
			for (i = 0; i < 3; i++){
				
				//teki[i][j][k].count_MAX = 50;//�G�������[�v���Ƃɓ�����
				//teki[i][j][k].count = teki[i][j][k].count_MAX;
				teki[i][j][k].x = (lx - 1) + lx*k;//�΂̓G�̂����W
				//teki[i][j][k].kankaku = teki[i][j][k].kankaku_sk;
				teki[i][j][k].sp = lx / 2;//�G�̈��̈ړ�����
				teki[i][j][k].dead = 0;//�G�ɒe�������������ǂ����i�P�œ�����j
			}
		}
		teki[0][1][k].dead = 1;//�]���ȓG���E��
	}
}

/**********************************
*    �Q�[���R���g���[�����C��    *
**********************************
*/
void game_main()
{
	//static int alpha;
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
			alpha = 255;
		}

		T_Cnt--;//�J�E���^������
		break;


	case 1://�^�C�g���̃t�F�[�h�A�E�g
		if (alpha <= 0) {
			G_mode = 10;//�Q�[���{�҂�
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
			fade_mode = 1;
			break;
		}
		alpha-=4;
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , alpha) ;
		DrawGraph(70, 80, title, TRUE);//�^�C�g���̕\��
		break;
	case 10://�Q�[���{��
		if (fade_mode == 1){//�t�F�[�h�C��
			if (alpha <= 251){
				alpha += 2;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			}
		}
		else if (fade_mode == 2){//�t�F�[�h�A�E�g
			alpha -= 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			if (alpha <= 0 ){
							
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				G_mode = 2;//�Q�[���I�[�o�[��ʂ�
				break;
				
			}
			
		}
		else if (fade_mode == 3){//�t�F�[�h�A�E�g

			if (alpha <= 0){

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

				G_mode = 3;//�N���A��ʂ�
				break;

			}
			alpha -= 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		}
		


		////////////////////////////////////////////////////////////////////////////////////


		
		
		//�G�֌W

		haji_chk();
		teki_idou();//�G�ړ��֐�

		sentou_chk();//��ŒN���擪�ɂ��邩

		//�G�e����

		tekidan_hassha();
			//�G�e�ړ�
		   
			tekidan_idou();
			gover_chk();//�G�������̃��C���ɓ��B������Q�[���I�[�o�[

		
			teki_atari();//���@�̒e�ƓG�̓�����`�F�b�N
			jiki_atari();//�G�e�Ǝ��@�̓�����`�F�b�N
			

			hyouji_all();//�\���֐�
					
		
	/////////////////////////////////////////////////////////////////
					

		//�L�[����/////////////////
		//���@�̑���
			if ((Key_Info & 0x01) == 0x01 && jiki.x > 31 && stop == 0 ){
				jiki.x -= jiki.sp;//����
				
			}
			if ((Key_Info & 0x02) == 0x02 && jiki.x + lx < 450 + 31 && stop == 0 ){
				jiki.x += jiki.sp;//�E��
				
			}
		if ((key_trg & 0x10) == 0x10 && jiki.shot == 0 && stop == 0)
		{

			tama.x = jiki.x + 15; tama.y = jiki.y;//�e�Ɍ��݂̎��@���W���
			jiki.shot = 1;//�e�O�̔���
		}
		///////////////////////////////////
		if (fade_mode!=3) teki_nokori_chk();//�G�̎c��`�F�b�N
			
		counter();
	

		break;

	case 2://�Q�[���I�[�o�[
		if (alpha <= 251){
			alpha += 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			
		}
		DrawGraph(0, 0, GO, TRUE);

		if (alpha >= 253){
			WaitKey();
		}
		break;
		
	case 3://�N���A
		if (alpha <= 251){
			alpha += 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		}
		DrawGraph(0, 0, cl, TRUE);

		if (alpha >= 253){
			WaitKey();
		}
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

/////////  �\���֌W  //////////////////////
void haikei()
{
	DrawGraph(0, 0, bg, TRUE);//�w�i�̕\���֐�
	DrawFormatStringToHandle(64, 20, GetColor(255, 255, 255), FontHandle2, "Your Score %04d", ten.now);//���݃X�R�A�̕\��
	DrawFormatStringToHandle(450 + 32 - 192, 20, GetColor(255, 255, 255), FontHandle2, "Hi-Score %04d", ten.high);//�n�C�X�R�A�̕\��

}

	//���@�֌W�֐�
void hyouji_all(){
	//�w�i�E�X�R�A�\��
	haikei();
	zanki();

	////���@�̒e�\���֌W

	jikidan_idou();//���@�e�ړ�
	

	//���@�e
	if (jiki.shot == 1){
		jikidan_hyouji();
	}

	//���@�̕\��
	jiki_hyouji();//���@�̕\��



	//�G�e�\��
	
		tekidan_hyouji();//�G�e�\��
		//�G�{�̊֌W
		teki_hyouji();//�G�̕\��
	}

void jiki_hyouji(){//���@�̕\��



	if (jiki.dead == 0){
		DrawGraph(jiki.x, jiki.y, chr[3], TRUE);//���@�̕\��
		
	}
	else if (jiki.dead == 1){
		
		
		if (dead_cnt % 10 >= 5)
			DrawGraph(jiki.x, jiki.y, chr[5], TRUE);//���@�̕\��
		else if (dead_cnt % 10<5)
			DrawGraph(jiki.x, jiki.y, chr[6], TRUE);//���@�̕\��
		if (dead_cnt < 0){
			jiki.dead = 0;
			stop = 0;
			dead_cnt = 100;
		}
	}


}


void jikidan_idou(){//���@�e�ړ�
	if (jiki.shot == 1 && stop==0){
		tama.y -= jiki.t_sp;//�e�̂����W������
		if (tama.y + 16 < 0)
			jiki.shot = 0;

	}
}
void jikidan_hyouji(){//���@�̒e�\���֐�
	DrawGraph(tama.x, tama.y, tm[1], TRUE);//�e�O�`��
}
void zanki(){//�c�莩�@�\��

	for (i = 0; i < jiki.life; i++){
		DrawGraph(480 - lx*(1 + i), 480 - ly, chr[3], TRUE);//���@�̕\��

	}
}
	

//�G�֌W�֐�
void teki_hyouji(){//�G�\��
	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				if (teki[i][j][k].dead == 0){
					if (i == 0){
						DrawGraph(teki[i][0][k].x, teki[i][0][k].y, chr[2], TRUE);//�G�P�i�΁j�\��
					}
					else if (i == 1){
						DrawGraph(teki[i][j][k].x, teki[i][j][k].y, chr[1], TRUE);//�G�Q�i���F�j�\��
					}
					else if (i ==2){
						DrawGraph(teki[i][j][k].x, teki[i][j][k].y, chr[0], TRUE);//�G3�i���j�\��
					}
				}
			}
		}
	}
}



//////////////////////////////////////////////////////////////////////////////////

void tekidan_hassha(){
	
	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				teki[i][j][k].kankaku--;
				if (teki[i][j][k].dead == 0 && teki[i][j][k].sentou == 1){
					if (teki[i][j][k].kankaku <= 0 && teki[i][j][k].shot == 0 && stop == 0){
						teki[i][j][k].kankaku = teki[i][j][k].kankaku_sk;
						teki[i][j][k].shot = 1;//�ʃt���O�P
						teki[i][j][k].tama_x = teki[i][j][k].x + 15;
						teki[i][j][k].tama_y = teki[i][j][k].y;
					}
				}
			}
		}
	}
}
void tekidan_hyouji(){//�G�e�\��

	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				if (teki[i][j][k].shot == 1)
					DrawGraph(teki[i][j][k].tama_x, teki[i][j][k].tama_y, tm[0], TRUE);//�G�e�̕\��
			}
		}
	}
}

//�G�e�ړ�
void tekidan_idou(){
	for (i = 0; i<3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				if (teki[i][j][k].shot == 1 && stop == 0){
					teki[i][j][k].tama_y += teki[i][j][k].t_sp;//�G�e�̂����W������
					if (teki[i][j][k].tama_y + 16 >= 640)
						teki[i][j][k].shot = 0;//�G�e�t���O�O
				}
			}
		}
	}
}
//////////////////////





void teki_idou(){

	if (stop == 0){
		en_cnt--;
		if (haji == 0){


			if (en_cnt == 0){
				en_cnt = en_cnt_MAX;
				for (i = 0; i < 3; i++){
					for (j = 0; j < 2; j++){
						for (k = 0; k < 11; k++){

							teki[i][j][k].x += teki[i][j][k].sp;
						}
					}
				}
			}
		}
		else{
			if (en_cnt == 0){
				en_cnt = en_cnt_MAX;
				for (i = 0; i < 3; i++){
					for (j = 0; j < 2; j++){
						for (k = 0; k < 11; k++){
							teki[i][j][k].y += lx;
							teki[i][j][k].sp = ~teki[i][j][k].sp + 1;
							haji = 0;
						}
					}
				}

			}
		}
	}
}




//�G�������̃��C���ɓ��B������Q�[���I�[�o�[
void gover_chk(){
	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				if (teki[i][j][k].y >= jiki.y && teki[i][j][k].dead==0){
					stop = 1;
					fade_mode = 2;
					return;
				}
			}
		}
	}
}

void haji_chk(){
	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				if ((teki[i][j][k].x + 32 >= 480 - 1 && teki[i][j][k].sp>0) || (teki[i][j][k].x <= 31 && teki[i][j][k].sp < 0)){
					if (teki[i][j][k].dead == 0){
						haji = 1;
						break;
					}
				}
			}
		}
	}
}


///�e�ƓG�̓����蔻��
void teki_atari(){
	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				if (tama.x + 2 >= teki[i][j][k].x + 4 && tama.x <= teki[i][j][k].x + 32 - 4 && tama.y <= teki[i][j][k].y + 16 && tama.y + 16 >= teki[i][j][k].y){
					if (jiki.shot == 1 && teki[i][j][k].dead == 0){
						
						switch (i){
						case 0:
							ten.now += 100;//100�_�v���X
							break;
						case 1:
							ten.now += 50;//50�_�v���X
							break;
						case 2:
							ten.now += 10;//10�_�v���X
							break;
						}
						jiki.shot = 0;//�e�t���O�O
						teki[i][j][k].dead = 1;//�G���S
						teki_nokori--;//�G�c��̐�
					}
				}
			}
		}
	}
}

// �G�e�����@�ɓ���������
void jiki_atari(){
	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				if (teki[i][j][k].tama_x + 2 > jiki.x && teki[i][j][k].tama_x < jiki.x + 32 && teki[i][j][k].tama_y<jiki.y + 16 && teki[i][j][k].tama_y + 16>jiki.y){
					if (jiki.dead == 0 && teki[i][j][k].shot == 1){

						stop = 1;
						jiki.dead = 1;
						teki[i][j][k].shot = 0;

						teki[i][j][k].kankaku = teki[i][j][k].kankaku_sk;
						jiki.life--;//���@���C�t�[�[
						teki[i][j][k].tama_x = -100;
						teki[i][j][k].tama_y = -100;


						if (jiki.life < 0){
							alpha = 255;
							stop = 1;
							fade_mode = 2;//�t�F�[�h�A�E�g
							return;
							

						}
					}
				}
			}

		}

	}
}



void sentou_chk(){

	for (i = 0; i < 11; i++){
		if (teki[2][1][i].dead == 0){
			teki[2][1][i].sentou = 1;
			
		}else if (teki[2][0][i].dead == 0){
			teki[2][1][i].sentou = 0;

			teki[2][0][i].sentou = 1;
			
		}else if (teki[1][1][i].dead == 0){
			teki[2][0][i].sentou = 0;
			teki[1][1][i].sentou = 1;
			
		}else if (teki[1][0][i].dead == 0){
			teki[1][1][i].sentou = 0;
			teki[1][0][i].sentou = 1;
			
		}else if (teki[0][0][i].dead == 0){
			teki[1][0][i].sentou = 0;
			teki[0][0][i].sentou = 1;
		
		}else{
			teki[0][0][i].sentou = 0;
		}
	}

}

//�G�̎c��`�F�b�N
void teki_nokori_chk(){
	if (teki_nokori <= 44)
		en_cnt_MAX = 90;
	else if (teki_nokori <= 33)
		en_cnt_MAX = 80;
	else if (teki_nokori <= 22)
		en_cnt_MAX = 70;
	else if (teki_nokori <= 11)
		en_cnt_MAX = 60;
	else if (teki_nokori <= 5)
		en_cnt_MAX = 50;
	else if (teki_nokori <= 1)
		en_cnt_MAX = 30;
	else if (teki_nokori == 0){
		alpha = 0;
		fade_mode = 3;//�t�F�[�h�A�E�g
	}
}


//�J�E���^�֐�

void counter(){
	if (jiki.dead == 0 && stop == 0){
		jiki.count--;
	}

	if (jiki.dead == 1){
		dead_cnt--;
	
	}

}

