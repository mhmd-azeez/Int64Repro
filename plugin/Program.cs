using System.Runtime.InteropServices;

public class Program
{
    //[MethodImpl(MethodImplOptions.InternalCall)]
    // This doesn't work
    //[DllImport("__internal")]
    //public static unsafe extern long do_something(long n);

    // This doesn't work
    // public static unsafe extern long do_something(int n, int n2);

    // This works
    // public static unsafe extern long do_something(int n);

    // This works
    // public static unsafe extern int do_something(int n, int n2);

    // This doesn't work
    // public static unsafe extern int do_something(int n, int n2, int n3, int n4, int n5);

    // [DllImport("__Internal", CallingConvention = CallingConvention.Cdecl)]

    [DllImport("mylib")]
    public static extern void something();

    public static void Main(string[] args)
    {
        //var result = do_something(5);
        something();
        Console.WriteLine($"Hello World!");
    }
}