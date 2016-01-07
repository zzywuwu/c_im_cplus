#include <stdio.h>
#include <stdlib.h>

typedef struct op_type_s
{
	void (*op)(void);
}op_type;

typedef struct md5_type_s
{
	op_type op_t;
}md5_type;

typedef struct sha1_type_s
{
	op_type op_t;
}sha1_type;

typedef struct sms_s
{
	void (*send)(op_type *op_t);
	op_type *op_t;
}sms;

typedef struct normal_s
{
	sms s_t;
}normals;

typedef struct sos_s
{
	sms s_t;
}soss;

void setop(sms *ss,op_type *op_t)
{
	ss->op_t = op_t;
}

void normal_send(op_type *op_t)
{
	op_t->op();
    printf("normal_send!\n");
}

void sos_send(op_type *op_t)
{
	op_t->op();
    printf("sos_send!\n");
}

void md5_op(void)
{
	printf("md5_op ");
}

void sha1_op(void)
{
	printf("sha1_op ");
}

int main()
{
	sms *s = malloc(sizeof(normals));
	s->send = normal_send;

	sms *ss = malloc(sizeof(soss));
	ss->send = sos_send;

	op_type *md5 = malloc(sizeof(md5_type));
	md5->op = md5_op;

	op_type *sha1 = malloc(sizeof(sha1_type));
	sha1->op = sha1_op;
	
	setop(s,md5);
	s->send(s->op_t);

	setop(s,sha1);
	s->send(s->op_t);

	setop(ss,md5);
	ss->send(ss->op_t);

	setop(ss,sha1);
	ss->send(ss->op_t);

	return 0;
}
