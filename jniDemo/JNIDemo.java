
public class JNIDemo{
	static{
		System.loadLibrary("native");//加载动态库
	}

	public native static String hello(String m);/*native function*/
	public native static int sum(int[] a);

	public static void main(String args[]){
		JNIDemo d = new JNIDemo();
		int[] a ={1,2,3,4,5};
		/*
		call
		*/
		System.out.println(d.hello("jack"));//调用
		System.out.println(d.sum(a));
	}
}
