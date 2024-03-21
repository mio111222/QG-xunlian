package pojo;

public class login {
    private Integer id;
    private String userName;
    private String passWord;
    private Integer money;

    public Integer getId() {
        return id;
    }
    public String getUserName() {
        return userName;
    }
    public String getPassWord() {
        return passWord;
    }
    public Integer getMoney() {
        return money;
    }
    public void setId(Integer id) {
        this.id = id;
    }
    public void setUserName(String userName) {
        this.userName = userName;
    }
    public void setPassWord(String passWord) {
        this.passWord = passWord;
    }

    public void setMoney(Integer money) {
        this.money = money;
    }
    @Override
    public String toString() {
        return "Login{" +
                "id=" + id +
                ", userName=" + userName + '\'' +
                ", passWord='" + passWord + '\'' +
                ", money=" + money +
                '}';
    }
}
