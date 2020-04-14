set global log_bin_trust_function_creators=1;

drop function if exists selectPrerequisite;
drop table result;

delimiter //
create function selectPrerequisite(name varchar(8)) returns varchar(8)
begin
	declare res varchar(8);
	declare counter int;
	declare i int;
	declare cache varchar(8);
	create temporary table if not exists Result(id varchar(8));
	drop temporary table if exists temp;
	create temporary table temp (id varchar(8));
	insert into temp select a.id from (select prereq_id as id from prereq where course_id=name) as a left join (select id from result) as r on a.id=r.id where r.id is NULL; 
	insert into result select id from temp;
	set counter=0;
	set i=1;
	select count(*) from temp into counter;
	while counter>=i do
		set cache='';
		set res='';
		select id from temp limit i,1 into cache;
		select selectPrerequisite(cache) into res;
		set i=i+1;
    end while;
    set res=0;
    select count(*) from result into res;
	return res;
end //
delimiter ;

select selectPrerequisite(292);


-- 
--	select selectPrerequisite(a.cache) from (select prereq_id as cache from prereq where course_id=name as a) where a.;

-- select id from temp limit i,1 into cache;
-- selectPrerequisite(cache);
-- 
--		selectPrerequisite(cache);

--     select count(*) from result into res;

--		select selectPrerequisite(cache);

-- 292-> 399,664,489,704,416;



set global log_bin_trust_function_creators=1;

drop function if exists selectPrerequisite;
drop table result;

delimiter //
create function selectPrerequisite(name varchar(8)) returns varchar(8)
begin
	declare res varchar(8);
	declare counter int;
	declare i int;
	declare cache varchar(8);
	create temporary table if not exists result(id varchar(8));
	drop temporary table if exists temp;
	create temporary table temp (id varchar(8));
	insert into temp select a.id from (select prereq_id as id from prereq where course_id=name) as a left join (select id from result) as r on a.id=r.id where r.id is NULL; 
	insert into result select id from temp;
	set counter=0;
	set i=1;
	select count(*) from temp into counter;
	while counter>=i do
		set cache='';
		set res='';
		select id from temp limit i,1 into cache;
		call selectPrerequisite(cache);
		set i=i+1;
    end while;
    set res=0;
    select count(*) from result into res;
	return res;
end //
delimiter ;

select selectPrerequisite(292);
