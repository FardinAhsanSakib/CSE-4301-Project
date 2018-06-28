CREATE or replace procedure check_edit(input_id in number,_course in number, x out varchar2) as
	temp varchar2(30);
begin
	select name into temp
	from subject
	WHERE insid = input_id and scode=_course;
	x:=temp;
	exception
	when no_data_found
	then x:='not found';
end;
/
