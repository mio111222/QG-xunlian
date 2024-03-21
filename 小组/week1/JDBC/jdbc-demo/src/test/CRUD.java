
package test;

import com.alibaba.druid.pool.DruidDataSourceFactory;
import pojo.login;

import javax.sql.DataSource;
import java.io.FileInputStream;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;
import java.util.Scanner;



public class CRUD {
    public static void main(String[] args) throws Exception{
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入要执行的操作（1.查询所有；2.添加数据；3.修改数据；4.删除数据;0.退出）：");
        //System.out.println(System.getProperty("user.dir"));
        int choose = sc.nextInt();
        while ( choose != 0 ) {
            if (choose == 1) {
                testSelect();
            }
            if (choose == 2) {
                testadd();
            }
            if (choose == 3) {
                testUpdate();
            }
            if (choose == 4) {
                testDelete();
            }
            System.out.println("请输入要执行的操作（1.查询所有；2.添加数据；3.修改数据；4.删除数据;0.退出）：");
            choose = sc.nextInt();
        }
    }
    /*1.查询所有
        SQL：select * from login;*/
    public static void testSelect() throws Exception {
        //加载配置
        Properties prop = new Properties();
        prop.load(new FileInputStream("jdbc-demo/src/druid.properties"));
        //获取连接池对象
        DataSource dataSource = DruidDataSourceFactory.createDataSource(prop);
        //获取数据库连接
        Connection conn = dataSource.getConnection();
        //定义SQL
        String sql = "select * from login;";
        //获取pstmt对象
        PreparedStatement pstmt = conn.prepareStatement(sql);
        //执行SQL
        ResultSet rs = pstmt.executeQuery();
        //处理结果（用List<login>封装）
        login login = null;
        List<login> logins = new ArrayList<>();
        while (rs.next()) {
            int id = rs.getInt("id");
            String userName = rs.getString("username");
            String passWord = rs.getString("password");
            int money = rs.getInt("money");
            //封装
            login = new login();
            login.setId(id);
            login.setUserName(userName);
            login.setPassWord(passWord);
            login.setMoney(money);

            //装载集合
            logins.add(login);

        }
        System.out.println(logins);

        rs.close();
        pstmt.close();
        conn.close();

    }



    /*2.添加数据
    SQL：insert into login(username,password,money) values(?,?,?);*/

    public static void testadd() throws Exception {
        //读入数据
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入账号：");
        String userName = sc.nextLine();
        System.out.println("请输入密码：");
        String passWord = sc.nextLine();
        System.out.println("请输入金额：");
        int money = sc.nextInt();

        //加载配置
        Properties prop = new Properties();
        prop.load(new FileInputStream("jdbc-demo/src/druid.properties"));
        //获取连接池对象
        DataSource dataSource = DruidDataSourceFactory.createDataSource(prop);
        //获取数据库链接
        Connection conn = dataSource.getConnection();
        //定义SQL
        String sql = "insert into login(username,password,money) values(?,?,?)";
        //获取pstmt对象
        PreparedStatement pstmt = conn.prepareStatement(sql);
        //设置参数
        pstmt.setString(1,userName);
        pstmt.setString(2,passWord);
        pstmt.setInt(3,money);
        //执行SQL
        int count = pstmt.executeUpdate();
        //处理结果
        System.out.println(count  > 0);
        //释放资源
        pstmt.close();
        conn.close();
    }

    /*3.修改
    SQL:
    update login
        set username  = ?,
        password      = ?,
        money         = ?,
    where id = ?*/
    public static void testUpdate() throws  Exception {
        //读入数据
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入要修改的编号");
        int id = sc.nextInt();
        String ss = sc.nextLine();
        System.out.println("请输入要修改的名称");
        String userName = sc.nextLine();
        System.out.println("请输入要修改的密码");
        String passWord = sc.nextLine();
        System.out.println("请输入要修改的金额");
        int money = sc.nextInt();


        //加载配置
        Properties prop = new Properties();
        prop.load(new FileInputStream("jdbc-demo/src/druid.properties"));
        //获取连接池对象
        DataSource dataSource = DruidDataSourceFactory.createDataSource(prop);
        //获取数据库连接
        Connection conn = dataSource.getConnection();
        //定义SQL
        String sql = "update login\n" +
                "        set username  = ?,\n" +
                "        password = ?,\n" +
                "        money    = ?\n" +
                "    where id = ?";

        //获取对象
        PreparedStatement pstmt = conn.prepareStatement(sql);
        //设置参数
        pstmt.setString(1,userName);
        pstmt.setString(2,passWord);
        pstmt.setInt(3,money);
        pstmt.setInt(4,id);
        //执行SQL
        int count = pstmt.executeUpdate();
        //处理结果
        System.out.println(count > 0);
        //释放资源
        pstmt.close();
        conn.close();
    }

    /*4.删除
    SQL：delete from login where id = ?*/

    public static void testDelete() throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入要删除的编号：");
        int id = sc.nextInt();
        //加载配置
        Properties prop = new Properties();
        prop.load(new FileInputStream("jdbc-demo/src/druid.properties"));
        //获取连接池对象
        DataSource dataSource = DruidDataSourceFactory.createDataSource(prop);
        //获取数据库连接
        Connection conn = dataSource.getConnection();
        //定义SQL
        String sql = "delete from login where id = ?";
        //获取pstmt
        PreparedStatement pstmt = conn.prepareStatement(sql);
        //设置参数
        pstmt.setInt(1,id);
        //执行SQL
        int count = pstmt.executeUpdate();
        //处理结果
        System.out.println(count > 0);
        //释放资源
        pstmt.close();
        conn.close();
    }

}
