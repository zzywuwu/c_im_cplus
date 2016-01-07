#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct node_s
{
	void (*interrept)(struct node_s *cur,char *exp);
	int (*exe)(void *cur);
}node;

typedef struct expression 
{
	node n;
	node *vorp;
}expression;

typedef struct value_s 
{
	node n;
	int v;
}value;

typedef struct op_s 
{
	node n;
	node *left;
	node *right;
	char op_type;
}op;

int exe_value(void *cur)
{
	value *c = (value *)cur;
	
	return c->v; 
}

value * create_value(char *v)
{
	char tmp[128];

	value *n = (value *)malloc(sizeof(value));
	strncpy(tmp,v,1);
	printf("create_value %d\n",atoi(tmp));
	n->n.interrept = NULL;
	n->n.exe = exe_value;
	n->v = atoi(tmp);
	
	return n;
}

int exe_op(void *cur)
{
	op *c = (op *)cur;
	value *l = (value *)c->left;
	expression *r = (expression *)c->right;
	
	switch(c->op_type){
		case '+':		
			return l->n.exe((void *)l) + r->n.exe((void *)r);
		case '-':		
			return l->n.exe((void *)l) - r->n.exe((void *)r);
		case '*':
			return l->n.exe((void *)l) * r->n.exe((void *)r);
		default :
			printf("ERROR!\n");
			assert(1);
	}
	
	return 0;
}

int exe_expression(void *cur)
{
	expression *c = (expression *)cur;
	value *o = (value *)c->vorp;
	return o->n.exe(o);
}

node * create_expression(char *exp);

op * create_op(char op_type,struct node_s *left,char *exp)
{
	//printf("create_op %s\n",exp);
	op *c = (op *)malloc(sizeof(op));
	c->n.interrept = NULL;
	c->n.exe = exe_op;
	c->op_type = op_type;
	c->left = left;
	c->right = create_expression(exp);
	
	return c;
}

op * create_op2(char op_type,struct node_s *left,struct node_s *right)
{
	//printf("create_op %s\n",exp);
	op *c = (op *)malloc(sizeof(op));
	c->n.interrept = NULL;
	c->n.exe = exe_op;
	c->op_type = op_type;
	c->left = left;
	c->right = right;
	
	return c;
}

node * create_expression(char *exp)
{
	printf("create_expression %s\n",exp);
	expression *c = (expression *)malloc(sizeof(expression));
	c->n.interrept = NULL;
	c->n.exe = exe_expression;
	
	value *v,*v2;
	op *o,*o2 = NULL;
	
re:
	if(exp[1] == '+') {
		if (o2 == NULL ){
			v = create_value(exp);
			o = create_op('+',(node *)v,&exp[2]);
		}
		else {
			o = create_op('+',(node *)o2,&exp[2]);
			o2 = NULL;
		}
		c->vorp = (node *)o;
	}
	else if(exp[1] == '-') {
		if (o2 == NULL ){
			v = create_value(exp);
			o = create_op('-',(node *)v,&exp[2]);
		}
		else {
			o = create_op('-',(node *)o2,&exp[2]);
			o2 = NULL;
		}
		c->vorp = (node *)o;
	}
	else if(exp[1] == '*') {
		if (o2 == NULL ){
			v = create_value(exp);
			v2 = create_value(&exp[2]);
			o2 = create_op2('*',(node *)v,(node *)v2);
			exp++;
			exp++;
			goto re;
		}
		else {
			v2 = create_value(&exp[2]);
			o2 = create_op2('*',(node *)o2,(node *)v2);
			exp++;
			exp++;
			goto re;
		}
	}
	else if (exp[1] == '\0') {
		v = create_value(exp);
		c->vorp = (node *)v;
	}  

	return (node *)c;
}

int main()
{
	char str[128];
	
	strcpy(str,"2+3*4-3*7+3");
	
	node *root = create_expression(str);
	expression *e = (expression *)root;
	printf("%d\n",e->n.exe(root));

}

















