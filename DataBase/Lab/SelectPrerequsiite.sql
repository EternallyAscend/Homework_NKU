set global log_bin_trust_function_creators=1;
SET GLOBAL max_sp_recursion_depth =100;
drop procedure if exists selectPrerequisite;
drop table prerequisiteResult;
drop table prerequisiteTemp;
drop table prerequisiteAdd;
create temporary table if not exists prerequisiteResult(id varchar(8));
create temporary table if not exists prerequisiteTemp (id varchar(8));
delimiter //
create procedure selectPrerequisite(name varchar(8))
begin
	declare counter int;
	declare cache varchar(8);
	declare start int;
	declare end int;
	create temporary table if not exists prerequisiteResult(id varchar(8));
	create temporary table if not exists prerequisiteTemp (id varchar(8));
    drop table if exists prerequisiteAdd;
    create temporary table prerequisiteAdd(id varchar(8));
	select count(*) from prerequisiteTemp into start;
	insert into prerequisiteAdd select a.id from (select prereq_id as id from prereq where course_id=name) as a left join (select id from prerequisiteResult) as r on a.id=r.id where r.id is NULL; 
    insert into prerequisiteTemp select id from prerequisiteAdd;    
	insert into prerequisiteResult select id from prerequisiteAdd;
	select count(*) from prerequisiteTemp into end;
	set counter=start;
	while counter<end do
		set cache='';
		select id from prerequisiteTemp limit counter,1 into cache;
		call selectPrerequisite(cache);
		set counter=counter+1;
    end while;
end //
delimiter ;

call selectPrerequisite(292);

select * from prerequisiteResult;
select * from prerequisiteTemp;



delimiter //
create procedure clearPrerequisiteTemp()
begin
drop table if exists prerequisiteResult;
drop table if exists prerequisiteAdd;
end //
delimiter ;

call clearPrerequisiteTemp();

