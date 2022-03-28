# MyJniStudyProject

如何查看类中的字段和方法的签名？
```
// 命令行输入如下命令：
javap -s -p NativeLib.class

// 输出如下：
Compiled from "NativeLib.java"
public class com.example.mynativelib.NativeLib {
  public com.example.mynativelib.NativeLib();
    descriptor: ()V

  public static void loadSoFile();
    descriptor: ()V

  public native java.lang.String stringFromJNI();
    descriptor: ()Ljava/lang/String;

  public native java.lang.String addString(java.lang.String, java.lang.String);
    descriptor: (Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;

  public native void testCStudy(java.lang.String);
    descriptor: (Ljava/lang/String;)V

  static {};
    descriptor: ()V
}
```