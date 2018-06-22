CREATE or replace procedure check_teacher(input_id in number, x out varchar2) as
	temp varchar2(30);
begin
	select password into temp
	from teacher
	WHERE id = input_id;
	x:=temp;
	exception
	when no_data_found
	then x:='not found';
end;
/
