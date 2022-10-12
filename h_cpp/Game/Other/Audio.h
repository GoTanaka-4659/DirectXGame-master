#pragma once
#include <xaudio2.h>
#include <cstdint>
#include <wrl.h>
#include <map>
#include <string>

class Audio
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	/*using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;*/

public:
	// チャンクヘッダ
	struct ChunkHeader
	{
		char id[4]; // チャンク毎のID
		int32_t size;  // チャンクサイズ
	};

	// RIFFヘッダチャンク
	struct RiffHeader
	{
		ChunkHeader chunk;   // "RIFF"
		char type[4]; // "WAVE"
	};

	// FMTチャンク
	struct FormatChunk
	{
		ChunkHeader chunk; // "fmt "
		WAVEFORMATEX fmt; // 波形フォーマット
	};

	// 音声データ
	struct SoundData
	{
		// 波形フォーマット
		WAVEFORMATEX wfex;
		// バッファの先頭アドレス
		BYTE *pBuffer;
		// バッファのサイズ
		unsigned int bufferSize;
	};

	void Initilize();

	void Finalize();

	void LoadWave(const char *filename);

	void Unload(SoundData *soundData);

	void PlayWave(std::string filename);
private:
	//XAudio2のインスタンス
	ComPtr<IXAudio2> xAudio2;

	std::map<std::string, SoundData>soundDatas_;
};

