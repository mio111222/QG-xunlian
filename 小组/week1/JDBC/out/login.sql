-- 删除login表
DROP TABLE IF EXISTS login;
-- 创建login表
CREATE TABLE login(
	id int not null PRIMARY KEY auto_increment,
	username VARCHAR(20),
	password VARCHAR(32),
	money int
);

-- 添加数据
INSERT INTO login VALUES(null,'zhangsan','123456','1000'),(null,'lisi','456789','2000'),(null,'wangwu','abcdef','2500');
SELECT * from login;






