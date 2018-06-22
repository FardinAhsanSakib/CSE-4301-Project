CREATE table teacher(
	id number,
	name varchar2(30) not null,
	password varchar2(30) not null,
	email varchar2(50),
	dept number not null,
	add constraints pk_admin primary key(id),
	foreign key(dept) references department(id)
);
