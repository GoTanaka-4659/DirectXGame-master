#include "LoadCSV.h"

void LoadCSV::ReadCSV(std::string filename)
{
	input_csv_file_path = filename;
	output_csv_file_path = filename;
}

void LoadCSV::Output()
{
	//std::string filepath = "Resource/maps/";
	//std::string extension = ".csv";
	//const std::string fullpath = filepath + input_csv_file_path + extension;
	//const char *fileName = fullpath.c_str();

	//std::vector<std::vector<std::vector<int>>> mapdata;

	//DirectX::XMINT3 size;
	////�}�b�v
	//std::ifstream file;

	//file.open(fullpath);
	//if (file.fail()) {
	//	assert(0);
	//}
	//else {
	//	mapdata.clear();
	//	int sizeX = 0, sizeY = 0, sizeZ = 0;
	//	std::string line;

	//	int mapingCountX = 0;
	//	int mapingCountY = 0;

	//	while (std::getline(file, line)) {
	//		std::istringstream line_stream(line);
	//		std::string key;
	//		std::getline(line_stream, key, ' ');

	//		if (key == "size") {
	//			DirectX::XMINT3 s{};
	//			line_stream >> s.x;
	//			line_stream >> s.y;
	//			line_stream >> s.z;
	//			sizeX = s.x;
	//			sizeY = s.y;
	//			sizeZ = s.z;
	//			mapdata.resize(sizeX);
	//			for (int x = 0; x < sizeX; ++x) {
	//				mapdata[x].resize(sizeY);
	//				for (int y = 0; y < sizeY; ++y) {
	//					mapdata[x][y].resize(sizeZ);
	//				}
	//			}
	//		}
	//		if (key == "map") {
	//			std::vector<int>hoge;
	//			hoge.resize(sizeZ);
	//			for (int i = 0; i < sizeZ; i++) {
	//				line_stream >> hoge[i];
	//			}
	//			for (int i = 0; i < sizeZ; i++) {
	//				mapdata[mapingCountX][mapingCountY][i] = hoge[i];
	//			}
	//			mapingCountX++;
	//			if (mapingCountX == sizeX) {
	//				mapingCountX = 0;
	//			}
	//		}
	//		if (key == "next") {
	//			mapingCountY++;
	//		}
	//	}
	//}

	//file.close();

	//map->LoadMap(mapdata, size);
}

void LoadCSV::Input()
{
}

void LoadCSV::Update()
{
	// �ǂݍ���csv�t�@�C�����J��(std::ifstream�̃R���X�g���N�^�ŊJ��)
	std::ifstream ifs_csv_file(input_csv_file_path);

	// ��������csv�t�@�C�����J��(std::ofstream�̃R���X�g���N�^�ŊJ��)
	std::ofstream ofs_csv_file(output_csv_file_path);

	std::ifstream ifs;

	// getline�֐���1�s���ǂݍ���(�ǂݍ��񂾓��e��str_buf�Ɋi�[)
	while (getline(ifs, str_buf)) {
		// �u,�v��؂育�ƂɃf�[�^��ǂݍ��ނ��߂�istringstream�^�ɂ���
		std::istringstream i_stream(str_buf);

		// �u,�v��؂育�ƂɃf�[�^��ǂݍ���
		while (getline(i_stream, str_conma_buf, ',')) {
			// csv�t�@�C���ɏ�������
			ofs_csv_file << str_conma_buf << ',';
		}
		// ���s����
		ofs_csv_file << std::endl;
	}
}
