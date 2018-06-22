CREATE table admin(
	id number,
	name varchar2(30) not null,
	password varchar2(30) not null,
	email varchar2(40),
	add constraints pk_admin primary key(id)
);
