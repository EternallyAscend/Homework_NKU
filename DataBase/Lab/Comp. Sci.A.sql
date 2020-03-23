select * from student2 where student2.dept_name = "Comp. Sci."; 
-- select * from student2; 
select count(*) from student2 where student2.name like "A%";
select count(*) from student2 where upper(left(student2.name,1))="A";