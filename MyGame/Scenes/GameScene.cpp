#include "GameScene.h"
#include"Input.h"
#include"SceneManager.h"
#include"Tutorial.h"
#include"Feed.h"
#include"Tuna.h"
#include"Egg.h"
#include"Player.h"
#include"imgui.h"
#include"Destroy.h"
#include"mHelper.h"
#include"SushiMove.h"
#include<fstream>
#include <algorithm>
#include"ResultScene.h"
#include"PlaceObj.h"
#include"Human.h"
GameScene::GameScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}
/// <summary>
/// ������
/// </summary>
void GameScene::Initialize()
{
	Sprite::LoadTexture(2, L"Resources/2d/Wave/wave1.png");
	Sprite::LoadTexture(3, L"Resources/2d/Wave/wave2.png");
	Sprite::LoadTexture(4, L"Resources/2d/Wave/wave3.png");
	Sprite::LoadTexture(5, L"Resources/2d/Wave/wave4.png");

	WaveSprite[0] = Sprite::Create(2, { -300,0 });
	WaveSprite[1] = Sprite::Create(3, { -300,0 });
	WaveSprite[2] = Sprite::Create(4, { -300,0 });
	WaveSprite[3] = Sprite::Create(5, { -300,0 });
	Sprite::LoadTexture(11, L"Resources/2d/BG.png");
	Sprite* BackGround_ = Sprite::Create(11, { 0,0 });
	BackGround.reset(BackGround_);

	for (int i = 0; i < _countof(WaveSprite); i++) {
		WaveSprite[i]->SetSize({ 400,400 });
	}
	CameraControl::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());
	sushinum.push_back(0);//�ŏ��̓}�O��
	sushis.push_back(new Tuna());
	sushis[0]->Initialize();
	//���i�̓���
	smove.push_back(new SushiMove());
	
	std::unique_ptr<Rail> newRail;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			Rail* newRail_ = new Rail();
			newRail_->SetPosition(RailPos[j][i]);
			newRail_->SetRotation(RailRot[j][i]);
			newRail.reset(newRail_);
			Rails.push_back(std::move(newRail));
		}
	}
	for (std::unique_ptr< Rail>& rail : Rails) {
		rail->Initialize();
	}

	//Player::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(CameraControl::GetInstance()->GetCamera());

	//�J�������Z�b�g
	f_Object3d::SetCamera(CameraControl::GetInstance()->GetCamera());
	//�O���t�B�b�N�p�C�v���C������
	f_Object3d::CreateGraphicsPipeline();
	PlaceObj::GetInstance()->Init();
	player = new Human();
	player->Initialize();
}


/// <summary>
/// �X�V����
/// </summary>
void GameScene::Update()
{ 
	CameraControl::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());
	Wave1or2();
	Wave3();

	for (std::unique_ptr<Rail>& rail : Rails) {
		rail->Update();
	}
	for (int i = 0; i < sushis.size(); i++) {
		if (sushis[i] != nullptr) {
			PlaceObj::GetInstance()->Update(sushis[i]);
		}
	}

	for (int i = 0; i < sushis2.size(); i++) {
		if (sushis2[i] != nullptr) {
			PlaceObj::GetInstance()->Update(sushis2[i]);
		}
	}
	PlaceObj::GetInstance()->SetIconSpritePos();
	//Player::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());
	WaveCont();
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {//�����ꂽ��
		ScoreSave(score);
		BaseScene* scene = new ResultScene(sceneManager_);//���̃V�[���̃C���X�^���X����
		SceneManager::GetInstance()->SetScene(SceneManager::RESULT);
		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
	}
	player->Update();
}

/// <summary>
/// �X�v���C�g�`��
/// </summary>
/// <param name="cmdList"></param>
void GameScene::SpriteDraw()
{
	Sprite::PreDraw();
	BackGround->Draw();
	Sprite::PostDraw();
	DirectXCommon::GetInstance()->ClearDepthBuffer();

}

/// <summary>
/// �`��
/// </summary>
/// <param name="cmdList"></param>
void GameScene::Draw()
{
	//�|�X�g�G�t�F�N�g�̕`��
	DirectXCommon::GetInstance()->BeginDraw();//�`��R�}���h�̏��ւ��
	SpriteDraw();
	for (std::unique_ptr<Rail>& rail : Rails) {
		rail->Draw();
	}
	for (int i = 0; i < sushis.size(); i++) {
		if (sushis[i] != nullptr) {
			sushis[i]->Draw();
		}
	}
	for (int i = 0; i < sushis2.size(); i++) {
		if (sushis2[i] != nullptr) {
			sushis2[i]->Draw();
		}
	}
	player->Draw();
	PlaceObj::GetInstance()->Draw();
	Sprite::PreDraw();
	for (int i = 0; i < _countof(WaveSprite); i++) {
		WaveSprite[i]->Draw();
	}
	Sprite::PostDraw();
	player->IconDraw();
	//��낤�Ƃ����������ŃG���[��f��
	ImGui::Begin("siz");

//	float x = PlaceObj::GetInstance()->Getpos().m128_f32[1];
	ImGui::End();
	//Player::GetInstance()->Draw();
	DirectXCommon::GetInstance()->EndDraw();

}
void GameScene::Finalize()
{
	//delete postEffect;
	delete Gamesprite;
}

int GameScene::RetrandCount()
{
	switch (fase)
	{
	case GameScene::WAVE1:
		return rand() % 240 + 200;
		break;
	case GameScene::WAVE2:
		return rand() % 180 + 140;
		break;
	case GameScene::WAVE3:
		return rand() % 240 + 200;
		break;
	case GameScene::WAVE4:
		return 0;
		break;
	case GameScene::CLEAR:
		return 0;
		break;
	default:
		return 0;
		break;
	}
}

void GameScene::WaveCont()
{
	switch (fase)
	{
	case GameScene::WAVE1:
		if (ETime[WAVE1] <= 1.0f) {
			ETime[WAVE1] += 0.01f;
		}
		WaveSprite[WAVE1]->SetPosition({ Easing::EaseOut(ETime[WAVE1], -300, 100),100 });
		if (SushiDeathCount > 1) {
			ETime[WAVE1] = 0;
			fase = WAVE2;
		}
		
		break;
	case GameScene::WAVE2:
		if (ETime[WAVE1] <= 1.0f) {
			ETime[WAVE1] += 0.01f;
		}
		WaveSprite[WAVE1]->SetPosition({ Easing::EaseOut(ETime[WAVE1], 100, -300),100 });

		if (ETime[WAVE2] <= 1.0f&& ETime[WAVE1] >= 1.0f) {
			ETime[WAVE2] += 0.01f;
		}
		WaveSprite[WAVE2]->SetPosition({ Easing::EaseOut(ETime[WAVE2], -300, 100),100 });
		if (SushiDeathCount > 3) {
			ETime[WAVE2] = 0;
			sushinum2.push_back(0);//�ŏ��̓}�O��
			sushis2.push_back(new Tuna());
			sushis2[0]->Initialize();
			//���i�̓���
			smove2.push_back(new SushiMove());

			fase = WAVE3;
		}
		break;
	case GameScene::WAVE3:
		if (ETime[WAVE2] <= 1.0f) {
			ETime[WAVE2] += 0.01f;
		}
		WaveSprite[WAVE2]->SetPosition({ Easing::EaseOut(ETime[WAVE2], 100, -300),100 });

		if (ETime[WAVE3] <= 1.0f) {
			ETime[WAVE3] += 0.01f;
		}

		WaveSprite[WAVE3]->SetPosition({ Easing::EaseOut(ETime[WAVE3], -300, 100),100 });

		break;
	case GameScene::WAVE4:
		break;
	case GameScene::CLEAR:
		break;
	default:
		break;
	}
}

void GameScene::Wave1or2()
{
	placeC++;

	if (placeC % RandPlaceCount == 0) {
		sushinum.push_back(rand() % 2);
		if (sushinum.back() == 0) {
			sushis.push_back(new Tuna());
			sushis.back()->Initialize();
		} else if (sushinum.back() == 1) {
			sushis.push_back(new Egg());
			sushis.back()->Initialize();
		}
		smove.push_back(new SushiMove());
		RandPlaceCount = RetrandCount();
		placeC = 0;
	}
	for (int i = 0; i < sushis.size(); i++) {
		if (sushis[i] != nullptr) {
			smove[i]->Wave1or2move(sushis[i]);
			sushis[i]->Update();
			if (sushis[i]->GetDead() || sushis[i]->GetHP() <= 0) {
				SushiDeathCount++;
				Destroy(sushis[i]);
			}
		}
	}
}

void GameScene::Wave3()
{
	if (fase == WAVE3) {
		placeC2++;
	}

	if (placeC2 % RandPlaceCount2 == 0&&placeC2!=0) {
		sushinum2.push_back(rand() % 2);
		if (sushinum2.back() == 0) {
			sushis2.push_back(new Tuna());
			sushis2.back()->Initialize();
		} else if (sushinum2.back() == 1) {
			sushis2.push_back(new Egg());
			sushis2.back()->Initialize();
		}
		smove2.push_back(new SushiMove());
		RandPlaceCount2 = RetrandCount();
		placeC2 = 0;
	}
	for (int i = 0; i < sushis2.size(); i++) {
		if (sushis2[i] != nullptr) {
			smove2[i]->Wave3move(sushis2[i]);
			sushis2[i]->Update();
		if (sushis2[i]->GetDead()||sushis2[i]->GetHP() <= 0) {
				SushiDeathCount++;
				Destroy(sushis2[i]);
			}
		}
	}
}

void GameScene::LoadRanking() {
	std::ifstream file;
	file.open("Resources/csv/Ranking.csv");
	assert(file.is_open());

	csvRanking << file.rdbuf();

	file.close();
}

void GameScene::PushBackRank() {
	LoadRanking();
	std::string line;

	while (getline(csvRanking, line)) {
		//��͂��₷������
		std::istringstream line_stream(line);

		std::string word;
		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		getline(line_stream, word, ',');
		//"//"����n�܂�s�̓R�����g
		if (word.find("//") == 0) {
			//��΂�
			continue;
		}
		//�e�R�}���h
		if (word.find("FIRST") == 0) {
			getline(line_stream, word, ',');
			float F = (float)std::atof(word.c_str());
			Rank.push_back(F);
		} else if (word.find("SECOND") == 0) {
			getline(line_stream, word, ',');
			float S = (float)std::atof(word.c_str());
			Rank.push_back(S);
		} else if (word.find("THIRD") == 0) {
			getline(line_stream, word, ',');
			float T = (float)std::atof(word.c_str());
			Rank.push_back(T);
		} else if (word.find("NOW") == 0) {
			getline(line_stream, word, ',');
			float N = (float)std::atof(word.c_str());
			Rank.push_back(N);
			break;
		}

	}

}

void GameScene::ScoreSave(float Score) {
	PushBackRank();
	Rank.push_back(Score);
	std::sort(Rank.begin(), Rank.end(), std::greater<float>());//�~���\�[�g	
	std::ofstream file("Resources/csv/Ranking.csv");
	file << "FIRST" << ',';
	file << Rank[0] << ',';
	file << std::endl;
	file << "SECOND" << ',';
	file << Rank[1] << ',';
	file << std::endl;
	file << "THIRD" << ',';
	file << Rank[2] << ',';
	file << std::endl;
	file << "NOW" << ',';
	file << Score << ',';
	file << std::endl;
	file.close();

}