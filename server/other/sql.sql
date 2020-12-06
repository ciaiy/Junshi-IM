 create table msg(msgId VARCHAR(100) primary key  not null , cid varchar(128), message varchar(512), type int, sourceName varchar(50), sourceType int, sourceUid varchar(50), ext varchar(128), createTime bigint);

 

--  insert into msg (msgid  , cid, message, type, sourceName, sourceType, sourceUid, createTime) values ("123", "122", "123", 1, "123", 1, "123", 123213);