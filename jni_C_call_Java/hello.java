public class hello
{
    private String name;
    private int age;

    public static void main(String [] args)
    {
        System.out.println("hello,world");
    }

    public int sayhello_to(String name)
    {
        System.out.println("hello  "+name+" ! i am "+this.name+"  my age is "+this.age);
        return 123;
    }
}