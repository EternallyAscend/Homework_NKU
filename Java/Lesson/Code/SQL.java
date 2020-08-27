import java.sql.*;

public class SQL {
    public static void main(String []args) {
        int status = 1;
        try {
            if (status == 0) {
                throw new Exception("");
            }
            String url = "jdbc:mysql://localhost:3306/jpetstore?autoReconnect=true";
        }
        catch (Exception e) {
            e.printStackTrace();
        }

//        String mysql = "jdbc:mysql://localhost:3306/mail?user=root&password=root";
        String mysql = "jdbc:mysql://localhost:3306/mail?serverTimezone=Asia/Shanghai";
        String user = "root";
        String passwd = "root";
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            System.out.println("OK Load Finished.");
            Connection connection = DriverManager.getConnection(mysql,user,passwd);
            Statement statement = connection.createStatement();
            String sql = "select * from goods";
            ResultSet resultSet = statement.executeQuery(sql);
            while (resultSet.next()) {
                System.out.println(resultSet.getString("Goods_ID"));
                System.out.println(resultSet.getString("Goods_Type"));
            }
            statement.execute("insert into purchaser values(0,'Tom');");
//            statement.execute("update purchaser set purchaser_name = 'Tommy' where purchaser_name = 'Tom';");
            resultSet.close();
            statement.close();
            connection.close();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}
