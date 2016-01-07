#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const int MAX_PLAYER = 32;

static char pad[1024] = {0};

typedef struct unit_s
{
	void (*show_unit)(struct unit_s *current);
	void (*add_unit) (struct unit_s *current,struct unit_s *add_unit);
	char name[32]; /*name放play和org也行，因为在调度name的函数时，
					可以转化为play或org*/
}unit;

typedef struct play_s
{
	unit u;
}play;

typedef struct org_s
{
	unit u;
	unit *child[MAX_PLAYER];
	int totol;
	int pos;
}org;

void add_pad(void)
{
	char tmp[32] = {0} ;
	strcpy(tmp,"            ");
	strcat(pad,tmp);
}

void play_show(struct unit_s *current)
{
	printf("%s%s\n",pad,current->name);
}

void play_add_unit(struct unit_s *current,struct unit_s *add_unit)
{
	printf("ERROR ! %s don't add unit\n",current->name);
	assert(1);
}

void org_show(struct unit_s *current)
{
	int i;
	org * c = (org *)current;
	printf("%s%s(%s)\n",pad,current->name,"*");
		
	add_pad();
	for(i = 0; i < c->totol; i++) {
		c->child[i]->show_unit(c->child[i]);
	}	
}

void org_add_unit(struct unit_s *current,struct unit_s *add_unit)
{
	org * c = (org *)current;
	
	c->child[c->pos++] = add_unit;
	c->totol++;
}

unit * create_org(const char *name)
{
	unit *o = (unit *)calloc(1,sizeof(org));
	strcpy(o->name,name);
	o->show_unit = org_show;
	o->add_unit = org_add_unit;

	return o;
}

unit * create_play(const char *name)
{
	unit *o = (unit *)calloc(1,sizeof(play));
	strcpy(o->name,name);
	o->show_unit = play_show;
	o->add_unit = play_add_unit;

	return o;
}

int main()
{
	unit * root = create_org("总部");
	unit * pt = create_org("平台部");
	unit * cd = create_org("研发组");

	unit * lwq = create_play("lwq");
	unit * zzy = create_play("zzy");
	unit * xtx = create_play("xtx");
	unit * lwl = create_play("lwl");
	unit * zh = create_play("zh");
	unit * boss = create_play("boss");
	
	root->add_unit(root,boss);
	root->add_unit(root,zh);
	root->add_unit(root,pt);
	pt->add_unit(pt,lwl);
	pt->add_unit(pt,cd);
	cd->add_unit(cd,xtx);
	cd->add_unit(cd,lwq);
	cd->add_unit(cd,zzy);
	
	root->show_unit(root);
	
	lwl->add_unit(lwl,zzy);

	return 0;
}
