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
void jikidan();
void jiki_tenmetsu();
void teki_hyouji();
void tekidan();
void tekidan_idou();
void tekidan_hassha();
void zanki();

void teki_idou();//�G�ړ��֐�

void haji_chk();

void counter();//�J�E���^�֐�
void gover_chk();//�G�������̃��C���ɓ��B������Q�[���I�[�o�[

void teki_atari();
void jiki_atari();


//------ �ϐ��̒�` ------//
int key_trg, Key_Info, Key_Old;   // �L�[���
int ChkKAny;                             // �Ƃɂ����L�[�������ꂽ��true
int GLpCnt;                             // �Q�[�����[�v�J�E���^

int i, j,k;//���[�v�p

//�L�����摜�̃f�[�^
int title;//�^�C�g���摜�ǂݍ��ݗp
int bg; //�Q�[���{�Ҕw�i�摜�p
int GO;//�Q�[���I�[�o�[��ʓǂݎ��p
int bk;//�t�F�[�h�C���^�t�F�[�h�A�E�g�p
int wt;

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

int haji=0;//�G���[�ɗ����Ƃ��̃t���O

static int alpha;
int fade_mode=0;//�P���t�F�[�h�C���Q���t�F�[�h�A�E�g


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

	LoadDivGraph("../Img/en_my.bmp", 10, 5, 2, 32, 16, chr, 0);//�L�����N�^�ǂݍ���
	LoadDivGraph("../Img/missile.bmp", 2, 2, 1, 2, 16, tm, 0);//�e�摜�̓ǂݍ���
	title = LoadGraph("../Img/title.bmp");//�^�C�g���摜�ǂݍ���
	bg = LoadGraph("../Img/bg.jpg");//�Q�[���{�Ҕw�i�摜
	GO = LoadGraph("../Img/gover.jpg");//�Q�[���I�[�o�[���
	bk = LoadGraph("../Img/Black.png");//�t�F�[�h�p���
	wt = LoadGraph("../Img/white.png");//�t�F�[�h�p���

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
	
	

	

	
	for (i = 0; i < 11; i++){

		//teki[0][0][i].haji = 0;//�G���[�ɂ��邩�t���O

		teki[0][0][i].count_MAX = 50;//�G�������[�v���Ƃɓ�����
		teki[0][0][i].count = teki[0][0][i].count_MAX;

		teki[0][0][i] .x = (lx - 1) + lx*i;//�΂̓G�̂����W
		teki[0][0][i] .y = ly * 5;//�΂̓G�̏��������W
		teki[0][0][i] .kankaku_sk = rand() % 200 + 100;//�΂̓G�̒e�����Ԋu

		teki[0][0][i] .kankaku = teki[0][0][i] .kankaku_sk;
		teki[0][0][i] .sp = lx / 2;//�G�̈��̈ړ�����
		teki[0][0][i] .dead = 0;//�G�ɒe�������������ǂ����i�P�œ�����j
		
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

			if (alpha <= 0){
				G_mode = 2;//�Q�[���I�[�o�[
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


			}
			alpha -= 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		}
		


		////////////////////////////////////////////////////////////////////////////////////


		
		
		//�G�֌W

		haji_chk();
		teki_idou();//�G�ړ��֐�


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




		counter();
	

		break;

	case 2://�Q�[���I�[�o�[
		if (alpha <= 251){
			alpha += 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			
		}
		DrawGraph(0, 0, GO, TRUE);

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
	DrawFormatStringToHandle(64, 20, GetColor(120, 120, 120), FontHandle2, "Your Score %04d", ten.now);//���݃X�R�A�̕\��
	DrawFormatStringToHandle(450 + 32 - 192, 20, GetColor(120, 120, 120), FontHandle2, "Hi-Score %04d", ten.high);//�n�C�X�R�A�̕\��

}

	//���@�֌W�֐�
void hyouji_all(){
	//�w�i�E�X�R�A�\��
	haikei();
	zanki();

	////���@�̒e�\���֌W
	if (jiki.shot == 1){
		tama.y -= jiki.t_sp;//�e�̂����W������
		if (tama.y + 16 < 0)
			jiki.shot = 0;

	}

	//���@�e
	if (jiki.shot == 1){
		jikidan();
	}

	//���@�̕\��
	jiki_hyouji();//���@�̕\��



	//�G�e�\��
	
		tekidan();//�G�e�\��
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
void jikidan(){//���@�̒e�\���֐�
	DrawGraph(tama.x, tama.y, tm[0], TRUE);//�e�O�`��
}
void zanki(){//�c�莩�@�\��

	for (i = 0; i < jiki.life; i++){
		DrawGraph(480 - lx*(1 + i), 480 - ly, chr[3], TRUE);//���@�̕\��

	}
}
	

//�G�֌W�֐�
void teki_hyouji(){//�G�\��
	for (i = 0; i < 11; i++){
		if (teki[0][0][i].dead == 0){
			DrawGraph(teki[0][0][i].x, teki[0][0][i].y, chr[2], TRUE);//�G�P�̕\��
		}
	}
}



//////////////////////////////////////////////////////////////////////////////////

void tekidan_hassha(){
	
	for (i = 0; i < 11; i++){
		teki[0][0][i].kankaku--;
		if (teki[0][0][i].dead == 0)
		{
			if (teki[0][0][i].kankaku<=0 && teki[0][0][i].shot == 0 && stop == 0)
			{
				teki[0][0][i].kankaku = teki[0][0][i].kankaku_sk;
				teki[0][0][i].shot = 1;//�ʃt���O�P
				teki[0][0][i].tama_x = teki[0][0][i].x + 15;
				teki[0][0][i].tama_y = teki[0][0][i].y;

			}
			
		}
	}
}
void tekidan(){//�G�e�\��

	for (i = 0; i < 11; i++){
		if (teki[0][0][i].shot == 1)
			DrawGraph(teki[0][0][i].tama_x, teki[0][0][i].tama_y, tm[1], TRUE);//�G�e�̕\��
	}
}

//�G�e�ړ�
void tekidan_idou(){
	for (i = 0; i<11; i++){
		if (teki[0][0][i].shot == 1 && stop == 0){
			teki[0][0][i].tama_y += jiki.t_sp;//�G�e�̂����W������
			if (teki[0][0][i].tama_y + 16 >= 640)
				teki[0][0][i].shot = 0;//�G�e�t���O�O
		}
	}
}
//////////////////////


/////�ړ��֌W�֐�/////////////////////////
void teki_idou()
{
	if (stop == 0){
		
		if (haji == 0)
		{
			for (i = 0; i < 11; i++){
				teki[0][0][i].count--;
				if (teki[0][0][i].count == 0){
					teki[0][0][i].count = teki[0][0][i].count_MAX;
					teki[0][0][i].x += teki[0][0][i].sp;
				}
			}
		}
		else
		{
			for (i = 0; i < 11; i++){
				teki[0][0][i].count--;
				if (teki[0][0][i].count == 0){
					teki[0][0][i].count = teki[0][0][i].count_MAX;
					teki[0][0][i].y += lx;
					teki[0][0][i].sp = ~teki[0][0][i].sp + 1;
					haji = 0;
				}
			}



			
		}
	}
}
//�G�������̃��C���ɓ��B������Q�[���I�[�o�[
void gover_chk(){
	for (i = 0; i < 11; i++){
		if (teki[0][0][i].y >= jiki.y){
			stop = 1;
			fade_mode = 2;
			break;
		}
	}
}

void haji_chk(){
	for (i = 0; i < 11; i++){
		if ((teki[0][0][i].x + 32 >= 480 - 1 && teki[0][0][i].sp>0) || (teki[0][0][i].x <= 31 && teki[0][0][i].sp < 0)){
			if (teki[0][0][i].dead == 0){
				haji = 1;
				break;
			}
		}
	}
}


//�����蔻��
void teki_atari(){//�e�ƓG�̓����蔻��
	for (i = 0; i < 11; i++){
		if (tama.x + 2 >= teki[0][0][i].x + 4 && tama.x <= teki[0][0][i].x + 32 - 4 && tama.y <= teki[0][0][i].y + 16 && tama.y + 16 >= teki[0][0][i].y){
			if (jiki.shot == 1 && teki[0][0][i].dead == 0){
				ten.now += 100;//100�_�v���X
				jiki.shot = 0;//�e�t���O�O
				teki[0][0][i].dead = 1;//�G���S
			}
		}
	}
}

// �G�e�����@�ɓ���������
void jiki_atari(){
	for (i = 0; i<11; i++){
		if (teki[0][0][i].tama_x + 2 > jiki.x && teki[0][0][i].tama_x < jiki.x + 32 && teki[0][0][i].tama_y<jiki.y + 16 && teki[0][0][i].tama_y + 16>jiki.y){
			if (jiki.dead == 0 && teki[0][0][i].shot == 1){

				stop = 1;
				jiki.dead = 1;
				teki[0][0][i].shot = 0;

				teki[0][0][i].kankaku = teki[0][0][i].kankaku_sk;
				jiki.life--;//���@���C�t�[�[
				teki[0][0][i].tama_x = -100;
				teki[0][0][i].tama_y = -100;


				//��ʉE��HIT�\��

				char c[20];
				wsprintf(c, "HIT!");
				DrawString(500, 128, c, GetColor(255, 255, 255));

				if (jiki.life < 0){
					alpha = 255;
					fade_mode = 2;//�t�F�[�h�A�E�g
					
				}
			}

		}

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

