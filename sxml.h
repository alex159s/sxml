#ifndef __SXML_H__
#define __SXML_H__


//�����ֵܽڵ㲻���㣬���ӽڵ�ĸ��������Խڵ�ĸ���������Լ������У����ڵ�ĵڼ������ӽڵ㣩
//�����ֵ�����,�ڵ�û�к��Ӵ�ӡ��������ɣ�
//ԭʼ����û������


//��������
#define SXML_INDENT_COUNT		4

//����һ��ָ����������
typedef void *QUEUE[2];

#ifdef      _WIN32
#define		XAPI	__declspec(dllexport)
#else
#define		XAPI
#endif

#ifdef __cplusplus
#define 	XEXPORT extern "C"
#else
#define		XEXPORT extern 
#endif

typedef enum __sxml_type_t
{
	SXML_NORMAL,
	SXML_COMMENT,
	SXML_INNERTEXT,
	SXML_RAWDATA,
	SXML_USERDEF
}sxml_type_t;

//�ڵ����
typedef struct __sxml_alias_t
{
	QUEUE aq;
	long long type;//0,�Գƽڵ�,1���Գƽڵ�
	char* alias;
	char* append;
}sxml_alias_t;

typedef struct __sxml_parser_t
{
	QUEUE normal;//�Գƽڵ�
	QUEUE special;//���Գƽڵ�
}sxml_parser_t;

//ԭʼ���ݽṹ�壬Ҫ��Ҫ����
typedef struct __sxml_data_t
{
	long long 				size;//���ݴ�С
	void        			*data;//����ָ��
}sxml_data_t;

typedef struct __sxml_node_t
{
	char*					name;
	char*					append;//�����û��Զ���ڵ�
	long long				type;//��ͨ�ڵ㡢ע�ͽڵ㡢��Ƕ�ı��ڵ㡢ԭʼ���ݽڵ㡢�սڵ�;0,1,2,3,4
	long long 				indent;//����
	long long 				index;//����
	long long 				childCount;//���Ӹ���
	long long 				attrCount;//���Ը���
	unsigned char 			reserved[8];//����
	struct __sxml_node_t*	prevSibling;//��һ���ֵܽڵ�
	struct __sxml_node_t*	nextSibling;//��һ���ֵܽڵ�
	struct __sxml_node_t*	parent;//���ڵ�ָ��
	void*					data;//�������
	QUEUE					children;//�ӽڵ�����ͷָ��
	QUEUE					attrs;//��������ͷָ��
	QUEUE					nq;
}sxml_node_t;

typedef struct __sxml_attr_t
{
	struct __sxml_attr_t*	prevSibling;//��һ���ֵ�����
	struct __sxml_attr_t*	nextSibling;//��һ���ֵ�����
	struct __sxml_node_t*	owner;//���������ڵ�
	long long 				index;//����
	char*					name;
	char*					value;
	long long				type;//�ַ�������ֵ������;0,1,2
	QUEUE					aq;
}sxml_attr_t;

typedef struct __sxml_doc_t
{
	char					filename[256];
	char					version[8];
	char					charset[8];
	QUEUE					dq;
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

typedef struct __sxml_file_line_t
{
	const char* start;
	long long line;
	long long len;
}sxml_file_line_t;

typedef struct __sxml_file_info_t
{
	sxml_file_line_t* line_info;
	long long line_count;
}sxml_file_info_t;

XEXPORT XAPI 	sxml_doc_t* 		sxml_doc_new(const char* filename, const char* version, const char* charset);
XEXPORT XAPI 	sxml_node_t* 		sxml_node_new(const char* name);
XEXPORT XAPI 	sxml_node_t* 		sxml_rawdata_new(const void* data, long long size);
XEXPORT XAPI 	sxml_node_t* 		sxml_userdef_new(const char* start, const char* end, const void* data, long long size);
XEXPORT XAPI 	sxml_node_t*		sxml_innertext_new(const char* innertext);
XEXPORT XAPI 	sxml_node_t* 		sxml_comment_new(const char* comment);
XEXPORT XAPI 	sxml_attr_t* 		sxml_attr_new(const char* name, const char* value);
XEXPORT XAPI 	sxml_parser_t* 		sxml_parser_new();
XEXPORT XAPI 	sxml_alias_t* 		sxml_alias_new(char* name, char* append);
	
XEXPORT XAPI 	int 				sxml_add_attr2node(sxml_node_t* node, sxml_attr_t* attr);
XEXPORT XAPI 	int 				sxml_add_node2doc(sxml_doc_t* doc, sxml_node_t* node);
XEXPORT XAPI 	int 				sxml_add_subnode2node(sxml_node_t* node, sxml_node_t* child);
XEXPORT XAPI 	long long int 		sxml_add_alias2parser(sxml_parser_t* parser, sxml_alias_t* alias);
	
XEXPORT XAPI 	int 				sxml_del_node4attr(sxml_node_t* node, char* name);
XEXPORT XAPI 	int 				sxml_del_doc4node(sxml_doc_t* doc, char* name);
XEXPORT XAPI 	int 				sxml_del_node4subnode(sxml_node_t* node, char* name);
XEXPORT XAPI 	long long int 		sxml_del_parser4alias(sxml_parser_t* parser, char* name);
	
XEXPORT XAPI 	char*				sxml_node_print_buffered(sxml_node_t* node,int size);
XEXPORT XAPI 	char*				sxml_doc_print_buffered(sxml_doc_t* doc,int size);
XEXPORT XAPI 	char*				sxml_doc_print(sxml_doc_t* doc);
	
XEXPORT XAPI 	void 				sxml_attr_free(sxml_attr_t* attr);
XEXPORT XAPI 	void 				sxml_node_free(sxml_node_t* node);
XEXPORT XAPI 	void 				sxml_doc_free(sxml_doc_t* doc);
	
XEXPORT XAPI 	int 				sxml_save2file(sxml_doc_t* doc, const char* filename);
XEXPORT XAPI 	int 				sxml_save(sxml_doc_t* doc);
	
XEXPORT XAPI 	sxml_file_info_t* 	sxml_get_file_info(const char* value);
XEXPORT XAPI 	void 				sxml_print_file_info(sxml_file_info_t* info);
XEXPORT XAPI 	void 				sxml_free_file_info(sxml_file_info_t** info);
	
XEXPORT XAPI 	sxml_doc_t* 		sxml_doc_parse(const char* filename, const char* value, sxml_parser_t* parser);
XEXPORT XAPI 	sxml_doc_t* 		sxml_parse(const char* filename, sxml_parser_t* parser);
	
XEXPORT XAPI 	sxml_node_t* 		sxml_node_nextSibling(sxml_node_t* node);
XEXPORT XAPI 	sxml_node_t* 		sxml_node_prevSibling(sxml_node_t* node);
XEXPORT XAPI 	sxml_attr_t* 		sxml_attr_nextSibling(sxml_attr_t* attr);
XEXPORT XAPI 	sxml_attr_t* 		sxml_attr_prevSibling(sxml_attr_t* attr);
			
XEXPORT XAPI 	sxml_node_t* 		sxml_node_getChildByName(sxml_node_t* node, char* name);
XEXPORT XAPI 	sxml_attr_t* 		sxml_node_getAttrByName(sxml_node_t* node, char* name);

#endif




