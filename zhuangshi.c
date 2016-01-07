#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct iplayer_s
{
	void (*show)(struct iplayer_s *cur);
	void (*free)(struct iplayer_s *cur);
}iplayer;

typedef struct player_s
{
	iplayer i;
	char name[32];
}player;

typedef struct ibuff_s
{
	iplayer i;
	iplayer *obj;
	char name[32];
}ibuff;

typedef struct a_buff_s
{
	ibuff b;
}abuff;

typedef struct c_buff_s
{
	ibuff b;
}cbuff;

void iplayer_show(struct iplayer_s *cur)
{
	player *c = (player *)cur;
	printf("%s ",c->name);	
}

void iplayer_free(struct iplayer_s *cur)
{
	player *c = (player *)cur;
	printf("free %s\n",c->name);	
	free(cur);
}

void ibuff_show(struct iplayer_s *cur)
{
	ibuff *c = (ibuff *)cur;
	c->obj->show(c->obj);
	printf("--> %s ",c->name);	
}

void ibuff_free(struct iplayer_s *cur)
{
		ibuff *c = (ibuff *)cur;
		assert(c->obj);
		c->obj->free(c->obj);
		printf("ibuff_free %s\n",c->name);	
		free(cur);
}

iplayer * create_player(const char *name)
{
		iplayer *p =(iplayer *)calloc(1,sizeof(player));
		p->show = iplayer_show;
		p->free = iplayer_free;
		player *c = (player *)p;
		strcpy(c->name,name);
		
		printf("create player %s\n",name);
		
		return p;
}

iplayer * create_a_buff(const char *name,iplayer *obj)
{
		ibuff *p =(ibuff *)calloc(1,sizeof(abuff));
		p->i.show = ibuff_show;
		p->i.free = ibuff_free;
		p->obj = obj;
		strcpy(p->name,name);
		
		printf("create a buff %s\n",name);
		
		return (iplayer *)p;
}

iplayer * create_c_buff(const char *name,iplayer *obj)
{
		ibuff *p =(ibuff *)calloc(1,sizeof(cbuff));
		p->i.show = ibuff_show;
		p->i.free = ibuff_free;
		p->obj = obj;
		strcpy(p->name,name);
		
		printf("create c buff %s\n",name);
		
		return (iplayer *)p;
}

int main()
{
	iplayer * p = create_player("zzy");
	p->show(p);
	printf("\n");
	
	iplayer *a = create_a_buff("加血",p);
	a->show(a);
	printf("\n");
	
	iplayer *c = create_c_buff("回血",a);
	c->show(c);
	printf("\n");
	
	c->free(c);

	return 0;
}
