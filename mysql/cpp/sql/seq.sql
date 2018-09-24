drop database test;
create database test;
use test;
create table seq
(
appid int primary key,
no int default 0,
memo varchar(255)
);
