CREATE table student(
	id number,
	name varchar2(30) not null,
	dob varchar2(30) not null,
	email varchar2(30),
	password varchar2(30),
	semester number,
	dept number,
	add constraints pk_admin primary key(id),
	FOREIGN KEY (dept) REFERENCES department (id)
);
