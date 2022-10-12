#include "LoadCSV.h"

void LoadCSV::ReadCSV(std::string filename)
{
	input_csv_file_path = filename;
	output_csv_file_path = filename;
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
