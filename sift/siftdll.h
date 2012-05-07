#ifndef _SIFTDLL_H_
#define _SIFTDLL_H_

#define SIFT_API extern "C" _declspec(dllimport)

#define  imgpix unsigned char
#define SIFT_DESC_LEN				128	

//һ����ֵ����Ϣ
typedef struct
{
	int		y;			//�ؼ���ռ�����
	int		x;
	int 	octave;		//��������
	int 	scale;		//���ڲ���
	float	sub_sca;	//�ǲ���
	//ƽ������
	float   sig_space;	//��ǰ�ؼ����������߶ȿռ��ڵ�ƽ������
	float   sig_octave;	//��ǰ�ؼ�����һ�����ڵ�ƽ������
	//��ԭͼ��ֱ����µ�����
	float   ox;
	float   oy;
	float   orient;		//�ؼ���������
	float   descriptor[SIFT_DESC_LEN]; //�ؼ���������
}Feature;

//�洢һ��ֵ�������ڵ�
typedef struct feature
{
	Feature *feat;				//�洢һ���ؼ�����Ϣ
	struct feature *next;	//ָ����һ���ڵ�
	struct feature *prev;	//ָ��ǰһ���ڵ�
}FeatureNode;

//�洢���м�ֵ�������ͷ
typedef struct featureVect
{
	int			to_extr_num;		//���м�ֵ�����
	FeatureNode *first;				//ָ���һ�����
	FeatureNode	*cur_node;			//ָ������������һ�����
}FeatureVect;


//��Ҫexport��
SIFT_API FeatureVect* _sift_main(const char* infile, imgpix	*imgData, int width, int height, float wid, int db_img, float sigma0,\
								 float sigman, float contr_thr, int sift_border_dist, float ill_norm_thresh, int top_oct_reso);
SIFT_API void free_feature_nodes(FeatureVect *featVect);

#endif