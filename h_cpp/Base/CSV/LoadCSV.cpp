#include "LoadCSV.h"

void LoadCSV::ReadCSV(std::string filename)
{
	input_csv_file_path = filename;
	output_csv_file_path = filename;
}

void LoadCSV::Update()
{
    // 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
    std::ifstream ifs_csv_file(input_csv_file_path);

    // 書き込むcsvファイルを開く(std::ofstreamのコンストラクタで開く)
    std::ofstream ofs_csv_file(output_csv_file_path);

	std::ifstream ifs;

    // getline関数で1行ずつ読み込む(読み込んだ内容はstr_bufに格納)
    while (getline(ifs, str_buf)) {
        // 「,」区切りごとにデータを読み込むためにistringstream型にする
        std::istringstream i_stream(str_buf);

        // 「,」区切りごとにデータを読み込む
        while (getline(i_stream, str_conma_buf, ',')) {
            // csvファイルに書き込む
            ofs_csv_file << str_conma_buf << ',';
        }
        // 改行する
        ofs_csv_file << std::endl;
    }
}
