#include <cstdint>  // for int32_t
#include <iostream>
#include <unordered_map>  // for std::unordered_map
#include <thread>
#include <mutex>
#include <vector>
#include <atomic>
#include <random>
#include <chrono>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <climits>
#include <inttypes.h>
 
int fPrt = 1;
const int TMP_BUF_LEN = 256;
void PRT(const char *fmt, ...)
{
	if ( fPrt == 0 ) return;
	va_list ap;
	const int PRT_LEN_MAX = 1024;
	static char text[PRT_LEN_MAX];

	va_start(ap, fmt);
	int len = vsprintf( text, fmt, ap );
	va_end(ap);

	if ( len < 0 || len >= PRT_LEN_MAX ) { fprintf(stderr,"buf over\n"); exit(0); }
	fprintf(stderr,"%s",text);
}

static char debug_str[TMP_BUF_LEN];
void debug_set(const char *file, int line)
{
	char str[TMP_BUF_LEN];
	strncpy(str, file, TMP_BUF_LEN-1);
	const char *p = strrchr(str, '\\');
	if ( p == NULL ) p = file;
	else p++;
	sprintf(debug_str,"%s line=%d\n\n",p,line);
}
void debug_print(const char *fmt, ... )
{
	va_list ap;
	static char text[TMP_BUF_LEN];
	va_start(ap, fmt);
#if defined(_MSC_VER)
	_vsnprintf( text, TMP_BUF_LEN-1, fmt, ap );
#else
	 vsnprintf( text, TMP_BUF_LEN-1, fmt, ap );
#endif
	va_end(ap);
	static char text_out[TMP_BUF_LEN*2];
	sprintf(text_out,"%s%s",debug_str,text);
	PRT("%s\n",text_out);
	exit(0);
}
#define DEBUG_PRT (debug_set(__FILE__,__LINE__), debug_print)




/*
// cshogi  src/position.hpp から
struct PackedSfenValue
{
    PackedSfen sfen;// 局面
    s16 score;    	// Learner::search()から返ってきた評価値
    u16 move;    	// PVの初手
    u16 gamePly;	// 初期局面からの局面の手数。
    s8  game_result;// この局面の手番側が、最終的に勝なら1。負け -1。引分 0。
    u8  padding;	// 40 byteにするためのdummy
    // 32 + 2 + 2 + 2 + 1 + 1 = 40bytes
};
*/
#include <random>
#include <algorithm>
#include <vector>
#include <sys/stat.h>

typedef struct psv {
	int sfen[8];
	short score;
	unsigned short move;
	unsigned short gamePly;
	char game_result;
	char padding;
} PSV;

std::vector<PSV> psv;

void shuffle_psv(char *fname) {
	FILE *fp = fopen(fname,"rb");
	if ( !fp ) DEBUG_PRT("");
	struct stat st;
	if ( stat(fname, &st) ) DEBUG_PRT("");
	size_t sz = st.st_size;
	size_t all = sz / sizeof(PSV);
	size_t div = all / 100;
	psv.resize(all);
	PRT("all=%ld,sz=%ld bytes\n",all,sz);
	for (size_t i=0; i<all; i++) {
		PSV a;
		int n = fread(&a,sizeof(PSV),1,fp);
		if ( n == 0 ) break;
//		if ( n != sizeof(PSV) ) DEBUG_PRT("n=%d\n",n);
//		psv.push_back(a);
		psv[i] = a;
		if ( ((i+1)%div) == 0 ) PRT(".");
	}
	PRT("\nsize(psv)=%d,sz=%ld bytes\n",psv.size(),sz);
	if ( psv.size() * sizeof(PSV) != sz ) DEBUG_PRT("size err.");
	fclose(fp);

	std::mt19937 get_rand_mt(0); // seed 0
	std::shuffle(psv.begin(), psv.end(), get_rand_mt);

	fp = fopen("hoge.bin","wb");
	if ( !fp ) DEBUG_PRT("");
	for (size_t i=0; i<psv.size(); i++) {
		PSV a = psv[i];
		fwrite(&a,sizeof(PSV),1,fp);
	}
	fclose(fp);
}

// シャッフルされたpsvを1個ずつ順番に取り出して結合する。手抜きのシャッフル。理想は全部のindexだけをシャッフルしてランダムアクセス
void cat_shuffled_psv(int argc, char *argv[]) {
	const int MAX_N = 8;
	int N = argc - 1;
	if ( N > MAX_N ) DEBUG_PRT("");
	FILE *fp[MAX_N];
	struct stat st[MAX_N];
	size_t all_max = 0;
	size_t all_sz = 0;
	for (int i=0;i<N;i++) {
		fp[i] = fopen(argv[i+1],"rb");
		if ( !fp[i] ) DEBUG_PRT("i=%d");
		if ( stat(argv[i+1], &st[i]) ) DEBUG_PRT("");
		size_t sz = st[i].st_size;
		size_t all = sz / sizeof(PSV);
		all_sz += sz;
		if ( all > all_max ) all_max = all;
		PRT("%d:all=%ld,sz=%ld bytes\n",i,all,sz);
	}
	PRT("all_sz=%ld\n",all_sz);

	FILE *fpw = fopen("hoge.bin","wb");
	if ( !fpw ) DEBUG_PRT("");

	size_t write_sz = 0;
	size_t div = all_max / 100;
	PRT("all_max=%ld\n",all_max);
	for (size_t i=0; i<all_max; i++) {
		for (int j=0; j<N; j++) {
			PSV a;
			int n = fread(&a,sizeof(PSV),1,fp[j]);
			if ( n == 0 ) continue;
			fwrite(&a,sizeof(PSV),1,fpw);
			write_sz++;
		}
		if ( ((i+1)%div) == 0 ) PRT(".");
	}
	PRT("write_sz=%ld\n",write_sz);
	fclose(fpw);
}

void split_shuffled_psv(int argc, char *argv[]) {
	if ( argc!=2 ) DEBUG_PRT("");
	FILE *fp = fopen(argv[1],"rb");
	if ( !fp ) DEBUG_PRT("");
	struct stat st;
	if ( stat(argv[1], &st) ) DEBUG_PRT("");
	size_t sz = st.st_size;
	size_t all = sz / sizeof(PSV);
	size_t div = all / 100;
	psv.resize(all);
	PRT("all=%ld,sz=%ld bytes\n",all,sz);
	FILE *fp_out = NULL;
	int sep = 0;

	const int ALL = 1000000000;
	const int DIV = 2;
	const int ONE = ALL / DIV;
	for (size_t i=0; i<all; i++) {
		PSV a;
		int n = fread(&a,sizeof(PSV),1,fp);
		if ( n == 0 ) break;

		if ( (i%ONE)==0 && sep < DIV ) {
			if ( fp_out ) fclose(fp_out);
			char out_file[256];
			sprintf(out_file,"%s.%d",argv[1],sep++);
			fp_out = fopen(out_file,"wb");
			if ( !fp_out ) DEBUG_PRT("");
		}
		fwrite(&a,sizeof(PSV),1,fp_out);
		if ( ((i+1)%div) == 0 ) PRT(".");
	}
	PRT("\nsize(psv)=%d,sz=%ld bytes\n",psv.size(),sz);
//	if ( psv.size() * sizeof(PSV) != sz ) DEBUG_PRT("size err.");
	fclose(fp);
	fclose(fp_out);
}

void average_psv(int argc, char *argv[]) {
	if ( argc!=3 ) DEBUG_PRT("");
	const int MAX_N = 2;
	int N = 2;
	FILE *fp[MAX_N];
	struct stat st[MAX_N];
	for (int i=0;i<N;i++) {
		fp[i] = fopen(argv[i+1],"rb");
		if ( !fp[i] ) DEBUG_PRT("i=%d");
		if ( stat(argv[i+1], &st[i]) ) DEBUG_PRT("");
	}
	size_t sz = st[0].st_size;
	if ( sz != (size_t)st[1].st_size ) DEBUG_PRT("");
	size_t all = sz / sizeof(PSV);
	PRT("%d:all=%ld,sz=%ld bytes\n",N,all,sz);

	FILE *fpw = fopen("hoge.bin","wb");
	if ( !fpw ) DEBUG_PRT("");

	size_t write_sz = 0;
	size_t div = all / 100;
	for (size_t i=0; i<all; i++) {
		PSV a[2];
		for (int j=0; j<N; j++) {
			int n = fread(&a[j],sizeof(PSV),1,fp[j]);
			if ( n == 0 ) DEBUG_PRT("");
		}
		if ( a[0].sfen[0] != a[1].sfen[0] ) DEBUG_PRT("i=%ld",i);
		if ( a[0].gamePly != a[1].gamePly ) DEBUG_PRT("i=%ld",i);
		if ( a[0].move    != a[1].move    ) DEBUG_PRT("i=%ld",i);
		int s0 = a[0].score;
		int s1 = a[1].score;
		int ave = s0;
		if ( abs(s0) < 25000 ) {
//			ave = (s0 + s1)/2;
			float a = 0.25; //0.75;
			ave = (1-a)*s0 + a*s1;
		}
		a[0].score = (short)ave;
		if ( i < 1000 ) PRT("%3ld: %6d, %6d -> %6d,  Ply=%3d,move=%04x,result=%3d\n",i,s0,s1,ave,a[0].gamePly,a[0].move,a[0].game_result);
		fwrite(&a[0],sizeof(PSV),1,fpw);
		write_sz++;

		if ( ((i+1)%div) == 0 ) PRT(".");
	}
	PRT("write_sz=%ld\n",write_sz);
	fclose(fpw);
}

void change_a_to_b_psv(int argc, char *argv[]) {
	if ( argc!=2 ) DEBUG_PRT("");
	const int MAX_N = 1;
	int N = 1;
	FILE *fp[MAX_N];
	struct stat st[MAX_N];
	for (int i=0;i<N;i++) {
		fp[i] = fopen(argv[i+1],"rb");
		if ( !fp[i] ) DEBUG_PRT("i=%d");
		if ( stat(argv[i+1], &st[i]) ) DEBUG_PRT("");
	}
	size_t sz = st[0].st_size;
	size_t all = sz / sizeof(PSV);
	PRT("%d:all=%ld,sz=%ld bytes\n",N,all,sz);

	FILE *fpw = fopen("hoge.bin","wb");
	if ( !fpw ) DEBUG_PRT("");

	size_t write_sz = 0;
	size_t div = all / 100;
	for (size_t i=0; i<all; i++) {
		PSV a[2];
		for (int j=0; j<N; j++) {
			int n = fread(&a[j],sizeof(PSV),1,fp[j]);
			if ( n == 0 ) DEBUG_PRT("");
		}
		int s0 = a[0].score;
		int ave = s0;
		if ( abs(s0) < 25000 ) {
			double a = 756.0864962951762;	// 600.0(+2800で99%);  756.08(+3500で99%);   
			double v = s0/a;
			double u = 1.0 / ( 1.0 + exp(-v) );
			double b = 600.0;
			double s = 1.0 * b * log(u / (1.0-u));
			ave = (int)s;
		}
		a[0].score = (short)ave;
		if ( i < 1000 ) PRT("%3ld: %6d -> %6d,  Ply=%3d,move=%04x,result=%3d\n",i,s0,ave,a[0].gamePly,a[0].move,a[0].game_result);
		fwrite(&a[0],sizeof(PSV),1,fpw);
		write_sz++;

		if ( ((i+1)%div) == 0 ) PRT(".");
	}
	PRT("write_sz=%ld\n",write_sz);
	fclose(fpw);
}

int main(int argc, char *argv[])
{
	if ( sizeof(PSV) != 40 ) DEBUG_PRT("");
 //	split_shuffled_psv(argc, argv); return 0;
//	average_psv(argc, argv); return 0;
	change_a_to_b_psv(argc, argv); return 0;
	if ( argc<2 ) { PRT("./psvs input.bin     or ./psvs shuffled_1.bin shuffled_2.bin\n"); exit(0); }
	if ( argc==2 ) {
		shuffle_psv(argv[1]);
	} else {
		cat_shuffled_psv(argc,argv);
	}
	return 0;
}

