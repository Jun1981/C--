/************************************
*                                  *
*    �V���[�e�B���O�Q�[�����[�v    *
*                                  *
************************************
*/
//------ �C���N���[�h�t�@�C���̓ǂݍ��� ------//
#include "../DxLib/DxLib.h"
#include<windows.h>
#include<time.h>
#include <stdlib.h>
#define kazu 300
#define jikidan_kankaku 8 ;

//------ �֐��̃v���g�^�C�v�錾 ------//
void start();//�^�C�g�����
void key_check();           // �L�[���擾
void game_main();           // �Q�[���R���g���[�����C��
void init();                // �Q�[���V�X�e��������
void haikei();//�w�i�\��
void hyouji_all();//�\���S��
void jikidan_hassha();//���@�e����
void jiki_hyouji();
void jiki_sousa();
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
void sc_chk();//�_���v�Z
void fade();//�t�F�[�h�֐�
//�֐��錾�I���

//------ �ϐ��̒�` ------//
int Key_Trg, Key_Info, Key_Old;   // �L�[���
int ChkKAny;                             // �Ƃɂ����L�[�������ꂽ��true
int GLpCnt;                             // �Q�[�����[�v�J�E���^
int i, j, k,l;//���[�v�p
int title;//�^�C�g���摜�ǂݍ��ݗp
int bg; //�Q�[���{�Ҕw�i�摜�p
int GO;//�Q�[���I�[�o�[��ʓǂݎ��p
int cl;//�N���A��ʗp
int chr[10];//�L�����N�^�[�����摜�ǂݍ��ݗp�ϐ�
int tm[2];//�e�f�[�^�ǂݍ��ݗp�ϐ�
int FontHandle1;//�^�C�g���p�t�H���g�n���h��;//�t�H���g�n���h���P�p
int FontHandle2;//�Q�[���p�t�H���g�n���h��;//�t�H���g�n���h���Q�p
int migihaji;//�E�[�̂����W������ϐ�
int hidarihaji;//���[�̂����W�������ϐ�
int T_Cnt;//�^�C�g���̂o�t�r�g�@�r�o�`�b�d�_�ŗp

//���������K�v�ȕϐ��Q
int lx;//�L�����N�^���̒���
int ly;//�L�����N�^�c�̒���
int G_mode;//�Q�[�����[�h�؂�ւ��p
int stop;//�[�ɍs���������Ă�t���O
int UFO=0;//UFO�t���O
int dead_cnt;//���񂾂Ƃ��̃J�E���^
int en_cnt_MAX = 100;//�G�������[�v���Ƃɓ������ő�l
int en_cnt = en_cnt_MAX;//�G�������[�v���Ƃɓ�����
int haji ;//�G���[�ɗ����Ƃ��̃t���O
static signed int alpha;
int fade_mode=0 ;//�P���t�F�[�h�C���Q���t�F�[�h�A�E�g
int sentou[5][11];
int  teki_nokori ;//�G�̎c��
int  yoyuu=8;//���@�̓����蔻����ɂ߂�
struct par{
	int x;//x���W
	int y;//y���W
	int sp;//�X�s�[�h
	int t_sp;//�e�X�s�[�h
	int dead;//����ł邩�ǂ���
	int life;//�c�莩�@
	int count;//�J�E���^
	int count_MAX;//�J�E���^�ő�l
	int shot[10];//�e���o�����ǂ���
	int kankaku;//�G�̒e�����Ԋu
	int kankaku_sk;//�G�̒e�����Ԋu�����l
	int tama_x[10];
	int tama_y[10];
	int sentou;//���擪�ɂ��邩�ǂ���
	int flag;//
	int tama_cnt;//���@�e�̊Ԋu
};//�e�L�����̃p�����[�^
struct score{
	int now;//���݃X�R�A
	int high;//�n�C�X�R�A
}ten = { 0, 0 };
struct par teki[3][2][11];///�G�̍\���̐錾�i�����A���i�ڂ��A����ځj	
struct par jiki;//���@�̍\���̐錾
struct par tama[kazu];//���˂����e

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
		DrawFormatStringToHandle(500, 72, GetColor(255, 255, 255), FontHandle2, "%d", teki_nokori);//�G�̎c��̐�
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
	//�����ϐ����l�ݒ�
	lx = 32;//�L�����N�^���̒���
	ly = 16;//�L�����N�^�c�̒���
	G_mode = 0;//�Q�[�����[�h
	T_Cnt = 20;//�^�C�g���h�o�t�r�g�@�r�o�`�b�d�h�_�ŗp�J�E���^
	migihaji = 450 + 30;//�L�����N�^�`�ʗ̈�E�[�̂����W
	hidarihaji = 30;//�L�����N�^�`�ʗ̈捶�[�̂����W
	stop = 0;//�G�S�̂��X�g�b�v����
	UFO=0;//UFO�t���O�O
	dead_cnt=200;//���@���S�J�E���g�����l
	en_cnt_MAX=100;//�G�������[�v���Ƃɓ������̍ő�l
	en_cnt = en_cnt_MAX;//�G�������[�v���Ƃɓ�����
	haji = 0;//�G���[�ɗ����Ƃ��̃t���O
	alpha=0;//�t�F�[�h�p�ϐ�
	fade_mode=0;//�t�F�[�h���[�h
	teki_nokori=55;//�G�̎c��
	jiki.x = 225 + 32; jiki.y = 480 - (16 * 5), jiki.sp = 2; jiki.t_sp = 4; jiki.dead = 0; jiki.life = 3; //���@�̍\���̐錾
	ten.now = 0;//���݃X�R�A�̏�����
	jiki.tama_cnt=jikidan_kankaku;
	for (k = 0; k < 11; k++){
		teki[0][0][k].y = ly * 5;//�΂̓G�̏��������W
		teki[0][0][k].t_sp = 6;//�e�̑���

		teki[1][0][k].y = ly * 7;//���F�P���������W
		teki[1][0][k].t_sp = 4;//�e�̑���

		teki[1][1][k].y = ly * 9;//���F�Q���������W
		teki[1][1][k].t_sp = 4;//�e�̑���

		teki[2][0][k].y = ly * 11;//���P���������W
		teki[2][0][k].t_sp = 3;//�e�̑���

		teki[2][1][k].y = ly * 13;//���Q���������W
		teki[2][1][k].t_sp = 3;//�e�̑���

		//�G�̒e�����Ԋu�����l�ݒ�
		for (l = 0; l < 10; l++){
			teki[0][0][k].kankaku_sk = rand() % 30 + 15;//�΂̓G�̒e�����Ԋu
			teki[0][0][k].kankaku = teki[0][0][k].kankaku_sk;

			teki[1][0][k].kankaku_sk = rand() % 30 + 60;//���F1�G�̒e�����Ԋu
			teki[1][0][k].kankaku = teki[1][0][k].kankaku_sk;

			teki[1][1][k].kankaku_sk = rand() % 30 + 60;//���F2�G�̒e�����Ԋu
			teki[1][1][k].kankaku = teki[1][1][k].kankaku_sk;

			teki[2][0][k].kankaku_sk = rand() % 50 + 100;//���P�G�̒e�����Ԋu
			teki[2][0][k].kankaku = teki[2][0][k].kankaku_sk;

			teki[2][1][k].kankaku_sk = rand() % 50 + 100;//���Q�G�̒e�����Ԋu
			teki[2][1][k].kankaku = teki[2][1][k].kankaku_sk;
		}

		//�G�֌W�����l
		for (j = 0; j < 2; j++){
			for (i = 0; i < 3; i++){
				for (l = 0; l < 10; l++){
					teki[i][j][k].shot[l] = 0;//�G�V���b�g�t���O�O
				}
				teki[i][j][k].x = (lx - 1) + lx*k;//�΂̓G�̂����W
				teki[i][j][k].sp = lx / 2;//�G�̈��̈ړ�����
				teki[i][j][k].dead = 0;//�G�ɒe�������������ǂ����i�P�œ�����j
				teki[i][j][k].sentou=0;//�擪�t���O
			}
		}
		teki[0][1][k].dead = 1;//�]���ȓG���E��(�΂�2��ځj
	}
	for (i = 0; i < kazu; i++){
		tama[i].flag = 0;//�e���o�Ă��Ȃ�
	}
}

/**********************************
*    �Q�[���R���g���[�����C��    *
**********************************
*/

////���C��//////////////////////////////////////////////////////////////////////

void game_main()
{
	//static int alpha;
	// �Q�[���̏���������
	switch (G_mode)
	{
	case 0:
		start();//�X�^�[�g���
		break;
	case 1://�^�C�g���̃t�F�[�h�A�E�g
		if (alpha <= 0) {
			G_mode = 10;//�Q�[���{�҂�
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			fade_mode = 1;
			break;
		}
		alpha -= 4;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
 		DrawGraph(70, 80, title, TRUE);//�^�C�g���̕\��
		break;
	case 10://�Q�[���{��
		
		fade();//�t�F�[�h�C��/�A�E�g
			
		
		if (stop == 0){
			tekidan_hassha();//�G�e����
			teki_atari();//���@�̒e�ƓG�̓�����`�F�b�N
			gover_chk();//�G�������̃��C���ɓ��B������Q�[���I�[�o�[
			jiki_atari();//�G�e�Ǝ��@�̓�����`�F�b�N
			jiki_sousa();//���@�̈ړ�
			
			teki_idou();//�G�ړ��֐�
			haji_chk();
			jikidan_idou();//���@�e�ړ�
			tekidan_idou();//�G�e�ړ�
		}
		
		sentou_chk();//��ŒN���擪�ɂ��邩
		teki_nokori_chk();//�G�̎c��`�F�b�N
		hyouji_all();//�\���֐�
		counter();
		break;
	case 2://�Q�[���I�[�o�[
		sc_chk();
		if (alpha <= 251){
			alpha += 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		}else{
			WaitKey();
			
			if(GetKeyState(0x52)<0){
				init();
				G_mode = 1;//�Q�[����
				break;				
			}
		}
		//DrawGraph(0, 0, GO, TRUE);
	
			SetFontSize(32);// �����̑傫�����w�肷��
            DrawFormatString(100, 20, GetColor(255, 50, 50), " �Q�[���I�[�o�["); 
			DrawFormatString(40, 120, GetColor(255,50,50), "�X�R�A    :%08d�_", ten.now); //�@���݂̓_��
			DrawFormatString(40, 190, GetColor(255,50,50), "�n�C�X�R�A:%08d�_", ten.high); //�@�n�C�X�R�A
			DrawFormatString(40, 290, GetColor(255,50,50), "������x:R"); //�@���݂̓_��
			DrawFormatString(40, 360, GetColor(255,50,50), "��߂�  :ESC"); //�@�n�C�X�R�A
	      
			
		break;
	case 3://�N���A
		sc_chk();
		if (alpha <= 251){
			alpha += 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		}else {			
			WaitKey();
			if(GetKeyState(0x52)<0){
				init();
				G_mode=1;//�Q�[����
				break;				
			}
		}
		SetFontSize(32);// �����̑傫�����w�肷��		
			DrawFormatString(100, 20, GetColor(0, 219, 255), "    �N���A"); 
			DrawFormatString(40, 90, GetColor(0, 219, 255),  "�X�R�A�@  :%08d�_", ten.now); //�@���݂̓_��
			DrawFormatString(40, 160, GetColor(0, 219, 255), "�n�C�X�R�A:%08d�_", ten.high); //�@�n�C�X�R�A
			
			DrawFormatString(40, 290, GetColor(0,219,255), "������x:R"); //�@���݂̓_��
			DrawFormatString(40, 360, GetColor(0,219,255), "��߂�  :ESC"); //�@�n�C�X�R�A
			
		//DrawGraph(0, 0, cl, TRUE);		
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////

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
	Key_Trg = Key_Info = 0;                                 // �L�[���N���A
	ChkKAny = false;
	if (CheckHitKey(KEY_INPUT_LEFT))   { Key_Info |= 0x01; }
	if (CheckHitKey(KEY_INPUT_RIGHT))  { Key_Info |= 0x02; }
	if (CheckHitKey(KEY_INPUT_UP))     { Key_Info |= 0x04; }
	if (CheckHitKey(KEY_INPUT_DOWN))   { Key_Info |= 0x08; }
	if (CheckHitKey(KEY_INPUT_SPACE))  { Key_Info |= 0x10; }
	if (CheckHitKey(KEY_INPUT_Z))      { Key_Info |= 0x20; }
	if (CheckHitKey(KEY_INPUT_ESCAPE)) { Key_Info |= 0x40; }
	if (CheckHitKeyAll()) { ChkKAny = true; }                    // ���Ɂ[
	Key_Trg = (Key_Info ^ Key_Old) & Key_Info;          // �L�[�g���K�[���Z�b�g
	Key_Old = Key_Info;                                     // �L�[���Z�[�u
}
/////////  �\���֌W  //////////////////////
void haikei()
{
	DrawGraph(0, 0, bg, TRUE);//�w�i�̕\���֐�
	DrawFormatStringToHandle(64, 20, GetColor(255, 255, 255), FontHandle2, "Your Score %04d", ten.now);//���݃X�R�A�̕\��
	DrawFormatStringToHandle(450 + 32 - 192, 20, GetColor(255, 255, 255), FontHandle2, "Hi-Score %04d", ten.high);//�n�C�X�R�A�̕\��
}
//�t�F�[�h
void fade(){
	if (fade_mode == 1){//�t�F�[�h�C��
		if (alpha <= 251){
			alpha += 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		}
	}
	else if (fade_mode == 2){//�t�F�[�h�A�E�g
		if (alpha <= 2){
			G_mode = 2;//�Q�[���I�[�o�[��ʂ�
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			//break;
		}
		alpha -= 2;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}
	else if (fade_mode == 3){//�t�F�[�h�A�E�g
		if (alpha <= 2){
			G_mode = 3;//�N���A��ʂ�
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			//break;
		}
		alpha -= 2;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}
}
//���@�֌W�֐�
void hyouji_all(){
	//�w�i�E�X�R�A�\��
	haikei();
	zanki();
	////���@�̒e�\���֌W
	//���@�e
	jikidan_hyouji();
	//�G�e�\��
	tekidan_hyouji();//�G�e�\��
	jiki_hyouji();//���@�̕\��
	teki_hyouji();//�G�̕\��
}
void jiki_hyouji(){//���@�̕\��
	if (jiki.dead == 0){
		DrawGraph(jiki.x, jiki.y, chr[3], TRUE);//���@�̕\��
	}
	else if (jiki.dead == 1){
		if (dead_cnt % 10 >= 5)
			DrawGraph(jiki.x, jiki.y, chr[5], TRUE);//���@�̕\��
		else if (dead_cnt % 10 < 5)
			DrawGraph(jiki.x, jiki.y, chr[6], TRUE);//���@�̕\��
	}

}
//���@�̑���
void jiki_sousa() {
	if ((Key_Info & 0x01)== 0x01 && jiki.x > 31){
		jiki.x -= jiki.sp;//����
	}
	if ((Key_Info & 0x02) == 0x02 && jiki.x + lx < 450 + 31){
		jiki.x += jiki.sp;//�E��
	}
	//if (Key_Trg == 0x10){
		if ( (Key_Trg & 0x10) == 0x10 ){
			if(jiki.tama_cnt<=0){
				jiki.tama_cnt=jikidan_kankaku;
		jikidan_hassha();//���@�e����
			}
	}
}
///////////////////////////////////
void jikidan_hassha(){
	for (i = 0; i < kazu; i++){
		if (tama[i].flag == 0 && stop == 0){
			tama[i].x = jiki.x + 15; tama[i].y = jiki.y;//�e�Ɍ��݂̎��@���W���
			tama[i].flag = 1;//�e�O�̔���
			return;
		}
	}
}
void jikidan_idou(){//���@�e�ړ�
	for (i = 0; i < kazu; i++){
		if (tama[i].flag == 1){
			tama[i].y -= jiki.t_sp;//�e�̂����W������
			if (tama[i].y + 16 < 0)//���@�e����ɒB������t���O�O
				tama[i].flag = 0;
		}
	}
}
void jikidan_hyouji(){//���@�̒e�\���֐�
	for (i = 0; i < kazu; i++){
		if (tama[i].flag == 1){
			DrawGraph(tama[i].x, tama[i].y, tm[1], TRUE);//�e�O�`��
		}
	}
}
void zanki(){//�c�莩�@�\��
	for (i = 0; i < jiki.life; i++){
		DrawGraph(480 - lx*(1 + i), 480 - ly, chr[3], TRUE);//���@�̕\��
	}
}
//�G�\��
void teki_hyouji(){//�G�\��
	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				if (teki[i][j][k].dead == 0){
					if (UFO == 0){
						if (i == 0){
							DrawGraph(teki[i][0][k].x, teki[i][0][k].y, chr[2], TRUE);//�G�P�i�΁j�\��
						}
						else if (i == 1){
							DrawGraph(teki[i][j][k].x, teki[i][j][k].y, chr[1], TRUE);//�G�Q�i���F�j�\��
						}
						else if (i == 2){
							DrawGraph(teki[i][j][k].x, teki[i][j][k].y, chr[0], TRUE);//�G3�i���j�\��
						}
					}
					else{
						DrawGraph(teki[i][j][k].x, teki[i][j][k].y,chr[4] , TRUE);//UFO�\��
					}
				}
			}
		}
	}
}
//�G�e����
void tekidan_hassha(){
	if (stop == 0){
		for (i = 0; i < 3; i++){
			for (j = 0; j < 2; j++){
				for (k = 0; k < 11; k++){
					teki[i][j][k].kankaku--;
					if (teki[i][j][k].dead == 0 && teki[i][j][k].sentou == 1){
						for (l = 0; l < 10; l++){
							if (teki[i][j][k].kankaku <= 0 && teki[i][j][k].shot[l] == 0 && stop == 0){
								teki[i][j][k].kankaku = teki[i][j][k].kankaku_sk;
								teki[i][j][k].shot[l] = 1;//�ʃt���O�P
								teki[i][j][k].tama_x[l] = teki[i][j][k].x + 15;
								teki[i][j][k].tama_y[l] = teki[i][j][k].y;
								return;
							}
						}
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
				for (l = 0; l < 10; l++){
					if (teki[i][j][k].shot[l] == 1)DrawGraph(teki[i][j][k].tama_x[l], teki[i][j][k].tama_y[l], tm[0], TRUE);//�G�e�̕\��
				}
			}
		}
	}
}
//�G�e�ړ�
void tekidan_idou(){
	
		for (i = 0; i < 3; i++){
			for (j = 0; j < 2; j++){
				for (k = 0; k < 11; k++){
					for (l = 0; l < 10; l++){
						if (teki[i][j][k].shot[l] == 1){
							teki[i][j][k].tama_y[l] += teki[i][j][k].t_sp;//�G�e�̂����W������
							if (teki[i][j][k].tama_y[l] + 16 >= 640)
								teki[i][j][k].shot[l] = 0;//�G�e�t���O�O
						}
					}
				}
			}
		}
	
}
//�G�ړ�
void teki_idou(){
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
//�G�������̃��C���ɓ��B������Q�[���I�[�o�[
void gover_chk(){
	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				if (teki[i][j][k].y >= jiki.y && teki[i][j][k].dead == 0){
					stop = 1;
					fade_mode = 2;
					return;
				}
			}
		}
	}
}
//�[�ɗ������ǂ���
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
					for (l = 0; l < kazu; l++){
						if (tama[l].x + 2 >= teki[i][j][k].x + 4 && tama[l].x <= teki[i][j][k].x + 32 - 4 && tama[l].y <= teki[i][j][k].y + 16 && tama[l].y + 16 >= teki[i][j][k].y){
							if (tama[l].flag == 1 && teki[i][j][k].dead == 0){
								tama[l].flag = 0;//�e�t���O�O
								teki[i][j][k].dead = 1;//�G���S
								teki_nokori--;//�G�c��̐�
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
								
							}
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
					for (l = 0; l<10; l++){
						if (teki[i][j][k].tama_x[l] + 2 > jiki.x+yoyuu && teki[i][j][k].tama_x[l] < jiki.x + 32-yoyuu && teki[i][j][k].tama_y[l]<jiki.y + 16 && teki[i][j][k].tama_y[l] + 16>jiki.y){
							if (jiki.dead == 0 && teki[i][j][k].shot[l] == 1 && stop==0){
								stop = 1;
								jiki.dead = 1;
								teki[i][j][k].shot[l] = 0;
								teki[i][j][k].kankaku = teki[i][j][k].kankaku_sk;
								jiki.life--;//���@���C�t�[�[
								teki[i][j][k].tama_x[l] = -100;
								teki[i][j][k].tama_y[l] = -100;								
								if (jiki.life < 0){
									alpha = 255;
									fade_mode = 2;//�t�F�[�h�A�E�g
									return;
								}
							}
						}
					}
				}
			}
		}	
}
//�G�̐擪�`�F�b�N
void sentou_chk(){
	for (i = 0; i < 11; i++){
		if (teki[2][1][i].dead == 0){
			teki[2][1][i].sentou = 1;
		}
		else if (teki[2][0][i].dead == 0){
			teki[2][1][i].sentou = 0;
			teki[2][0][i].sentou = 1;
		}
		else if (teki[1][1][i].dead == 0){
			teki[2][0][i].sentou = 0;
			teki[1][1][i].sentou = 1;
		}
		else if (teki[1][0][i].dead == 0){
			teki[1][1][i].sentou = 0;
			teki[1][0][i].sentou = 1;
		}
		else if (teki[0][0][i].dead == 0){
			teki[1][0][i].sentou = 0;
			teki[0][0][i].sentou = 1;
		}
		else{
			teki[0][0][i].sentou = 0;
		}
	}
}
//�G�̎c��ɉ���������
void teki_nokori_chk(){
	if (fade_mode!=3  && fade_mode!=2){
		if (teki_nokori <=5){
			if (UFO == 0){
				en_cnt_MAX = 5;
				UFO = 1;
				for (i = 0; i < 3; i++) {
					for (j = 0; j < 2; j++) {
						for (k = 0; k < 11; k++) {
							teki[i][j][k].t_sp = 6;
							for (l = 0; l < 10; l++) {
								teki[i][j][k].kankaku_sk = rand() % 25;
							}
						}
					}
				}
			}
		}
		if (teki_nokori == 11){
			en_cnt_MAX = 30;
		}
		if (teki_nokori == 22){
			en_cnt_MAX = 50;
		}
		if (teki_nokori == 33){
			en_cnt_MAX = 70;
		}
		if (teki_nokori == 44){
			en_cnt_MAX = 90;
		}
		if (teki_nokori == 0){
			alpha = 255;
			fade_mode = 3;//�t�F�[�h�A�E�g
		}
	}
}
//�X�R�A�`�F�b�N
void sc_chk(){
	if (ten.now > ten.high) ten.high = ten.now;
}
//�J�E���^�֐�
void counter(){
	jiki.tama_cnt--;
	if (jiki.dead == 0 && stop == 0){
		jiki.count--;
	}
	if (jiki.dead == 1){
		dead_cnt--;
		if (jiki.life >= 0){
			if (dead_cnt == 100){
				stop = 0;
			}
			else if (dead_cnt == 0){
				dead_cnt = 200;
				jiki.dead = 0;
			}
		}
	}
}
//�X�^�[�g���
void start(){
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
}
