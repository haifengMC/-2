#include <hiredis/hiredis.h>
#include <iostream>

using namespace std;

int main()
{
	redisContext* p_context = redisConnect("127.0.0.1", 6379);
	if (NULL != p_context)
	{
		redisReply* p_replyObj = (redisReply*)redisCommand(p_context, "set i1 10");
		if (REDIS_REPLY_STATUS == p_replyObj->type)cout << p_replyObj->str << endl;
		freeReplyObject(p_replyObj);

		p_replyObj = (redisReply*)redisCommand(p_context, "get i1");
		if (REDIS_REPLY_STRING == p_replyObj->type) cout << p_replyObj->str << endl;
		if (REDIS_REPLY_INTEGER == p_replyObj->type)cout << p_replyObj->integer << endl;
		freeReplyObject(p_replyObj);

		p_replyObj = (redisReply*)redisCommand(p_context, "set i1 apple");
		if (REDIS_REPLY_STATUS == p_replyObj->type) cout << p_replyObj->str << endl;
		freeReplyObject(p_replyObj);

		p_replyObj = (redisReply*)redisCommand(p_context, "get i1");
		if (REDIS_REPLY_STRING == p_replyObj->type) cout << p_replyObj->str << endl;
		if (REDIS_REPLY_INTEGER == p_replyObj->type)cout << p_replyObj->integer << endl;
		freeReplyObject(p_replyObj);

		p_replyObj = (redisReply*)redisCommand(p_context, "lpush i2 a e q d g c x d d w");
		if (REDIS_REPLY_INTEGER == p_replyObj->type) cout << p_replyObj->integer << endl;
		freeReplyObject(p_replyObj);

		p_replyObj = (redisReply*)redisCommand(p_context, "lrange i2 0 -1");
		if (REDIS_REPLY_ARRAY == p_replyObj->type)
		{
			for (int i = 0; i < p_replyObj->elements; i++)
			{
				if(REDIS_REPLY_STRING == p_replyObj->element[i]->type) 
					cout << p_replyObj->element[i]->str << " ";
			}
			cout << endl;
		}
		freeReplyObject(p_replyObj);

		p_replyObj = (redisReply*)redisCommand(p_context, "lrem i2 2 d");
		if (REDIS_REPLY_INTEGER == p_replyObj->type) cout << p_replyObj->integer << endl;
		freeReplyObject(p_replyObj);

		p_replyObj = (redisReply*)redisCommand(p_context, "lrange i2 0 -1");
		if (REDIS_REPLY_ARRAY == p_replyObj->type)
		{
			for (int i = 0; i < p_replyObj->elements; i++)
			{
				if (REDIS_REPLY_STRING == p_replyObj->element[i]->type)
					cout << p_replyObj->element[i]->str << " ";
			}
			cout << endl;
		}
		freeReplyObject(p_replyObj);

		freeReplyObject(redisCommand(p_context, "ltrim i2 1 0"));

		redisFree(p_context);
	}
}