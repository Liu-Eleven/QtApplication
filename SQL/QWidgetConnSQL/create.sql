PRAGMA foreign_keys=OFF;
BEGIN TRANSACTION;


CREATE TABLE PersonRole(
id integer primary key,		//id
Name text,			//姓名
Role text,			//人员类型
Phone text,			//电话
Biology text,			//生物特征
Passwd text			//密码
);

1.人物表
CREATE TABLE Person(
id INTEGER primary key,		//id
Name VARCHAR,			//姓名
Role TINYINT,			//人员类型 0-管理员  1-领导  2-值班员  3-持枪员
Phone VARCHAR,			//电话
Zhiwen TEXT,			//指纹特征
Zhijingmai TEXT,		//指静脉特征
Hongmo TEXT,			//虹膜特征
Passwd VARCHAR			//密码
);




INSERT INTO "Student" VALUES('LSY',' NV',21,1,' DHT');
INSERT INTO "Student" VALUES('RHZ',' NV',20,2,' XQZ');
INSERT INTO "Student" VALUES('ZY',' NV',20,3,' KZ');
INSERT INTO "Student" VALUES('NXY',' NV',20,4,' DG');
COMMIT;
