#ifndef __SXML_H__
#define __SXML_H__

//��������
#define SXML_INDENT_COUNT		4

//����һ��ָ����������
typedef void *QUEUE[2];

#define		XAPI	__declspec(dllexport)

#ifdef __cplusplus
#define 	XEXPORT extern "C"
#else
#define		XEXPORT extern 
#endif

//ԭʼ���ݽṹ�壬Ҫ��Ҫ����
typedef struct __sxml_data_t
{
	long long 	size;//���ݴ�С
	void        *data;//����ָ��
}sxml_data_t;

typedef struct __sxml_attr_t
{
	char*		name;
	char*		value;
	long long	type;//�ַ�������ֵ������;0,1,2
	QUEUE		aq;
}sxml_attr_t;

typedef struct __sxml_node_t
{
	char*					name;
	long long				type;//��ͨ�ڵ㡢ע�ͽڵ㡢��Ƕ�ı��ڵ㡢ԭʼ���ݽڵ㡢�սڵ�;0,1,2,3,4
	long long 				indent;//����
	struct __sxml_node_t*	parent;//���ڵ�ָ��
	void*					data;//�������
	QUEUE					children;//�ӽڵ�����ͷָ��
	QUEUE					attrs;//��������ͷָ��
	QUEUE					nq;
}sxml_node_t;

typedef struct __sxml_doc_t
{
	char		filename[256];
	char		version[8];
	char		charset[8];
	QUEUE		dq;
}sxml_doc_t;


typedef struct __sxml_hooks_t
{
    void *(*alloc)(unsigned int size);
    void (*free)(void *p);
}sxml_hooks_t,*sxml_hooks_ht;

typedef struct __sxml_buffer_t
{
	char *buffer; 
	int length; 
	int offset; 
}sxml_buffer_t,*sxml_buffer_ht;



XEXPORT XAPI sxml_doc_t* sxml_doc_new(const char* filename, const char* version, const char* charset);
XEXPORT XAPI sxml_node_t* sxml_node_new(const char* name);
XEXPORT XAPI sxml_node_t* sxml_rawdata_new(const char* name, const void* data, long long size);
XEXPORT XAPI sxml_node_t* sxml_innertext_new(const char* innertext);
XEXPORT XAPI sxml_node_t* sxml_comment_new(const char* comment);
XEXPORT XAPI sxml_node_t* sxml_empty_new(const char* name);
XEXPORT XAPI sxml_attr_t* sxml_attr_new(const char* name, const char* value);

XEXPORT XAPI int sxml_add_attr2node(sxml_node_t* node, sxml_attr_t* attr);
XEXPORT XAPI int sxml_add_node2doc(sxml_doc_t* doc, sxml_node_t* node);
XEXPORT XAPI int sxml_add_subnode2node(sxml_node_t* node, sxml_node_t* child);

XEXPORT XAPI char *sxml_node_print_buffered(sxml_node_t* node,int size);
XEXPORT XAPI char *sxml_doc_print_buffered(sxml_doc_t* doc,int size);
XEXPORT XAPI char *sxml_doc_print(sxml_doc_t* doc);

XEXPORT XAPI void sxml_attr_free(sxml_attr_t* attr);
XEXPORT XAPI void sxml_node_free(sxml_node_t* node);
XEXPORT XAPI void sxml_doc_free(sxml_doc_t* doc);

XEXPORT XAPI int sxml_save2file(sxml_doc_t* doc, const char* filename);
XEXPORT XAPI int sxml_save(sxml_doc_t* doc);

#endif




