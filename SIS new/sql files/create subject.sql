create table subject(
	scode number,
	name varchar2(50) not null,
	semester number not null,
	dept number not null,
	instid number not null,
	credit number not null,
	add constraints pk_subject primary key(scode),
	constraints fk_marks_inst foreign key(instid) references teacher(id),
	constraints fk_marks_dept foreign key(dept) references department(id)
)