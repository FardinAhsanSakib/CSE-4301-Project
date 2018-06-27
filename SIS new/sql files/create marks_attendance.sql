create table marks_attendance(
	sid number not null,
	scode number not null,
	semester number not null,
	dept number not null,
	marks number not null,
	tot_cls number not null,
	attend number not null,
	aca_year varchar2(50) not null,
	constraints fk_marks_stu foreign key(sid) references student(id),
	constraints fk_marks_sub foreign key(scode) references subject(scode),
	constraints fk_marks_dept foreign key(dept) references department(id)
)
