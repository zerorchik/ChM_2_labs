using System;

namespace cm2_lab_6
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = System.Text.Encoding.Default;
            Console.WriteLine("ПОЛІНОМ:\nx^4-3*x^3+x^2-2x-2=0\n");
            double[] a = { -0.8, 2.7 };
            double[] b = { -0.4, 3.1 };

            Console.WriteLine("Уведіть точність розрахунків: ");
            double e = Convert.ToDouble(Console.ReadLine());
            Console.WriteLine();

            for (int i = 0; i < 2; i++)
            {
                if (i == 0) Console.WriteLine("ПЕРШИЙ КОРІНЬ:\n");
                else if (i == 1) Console.WriteLine("ДРУГИЙ КОРІНЬ:\n");
                Console.WriteLine("x{0} Є [{1}; {2}]", i + 1, a[i], b[i]);
                MethodBisection(a[i], b[i], e);
                MethodHord(a[i], b[i], e);
                MethodNewton(a[i], b[i], e);
                Console.WriteLine();
            }
        }

        static double Func(double x)
        {
            int n = 4;
            int[] A = { -2, -2, 1, -3, 1 };
            double result = 0;
            for (int i = n; i >= 0; i--)
                result += A[i] * Math.Pow(x, i);
            return result;
        }
        static double Func1(double x)
        {
            int n = 3;
            int[] A = { -2, 2, -9, 4 };
            double result = 0;
            for (int i = n; i >= 0; i--)
                result += A[i] * Math.Pow(x, i);
            return result;
        }
        static double Func2(double x)
        {
            int n = 2;
            int[] A = { 2, -18, 12 };
            double result = 0;
            for (int i = n; i >= 0; i--)
                result += A[i] * Math.Pow(x, i);
            return result;
        }
        static void MethodBisection(double a, double b, double e)
        {
            int iteracii = 0;
            double x;
            if (Func(a) == 0) x = a;
            else if (Func(b) == 0) x = b;
            else
            {
                double c = 0;
                while (Math.Abs(b - a) > e || Math.Abs(Func(c)) > e)
                {
                    c = (a + b) / 2;
                    if (Func(a) * Func(c) < 0) b = c;
                    else a = c;
                    iteracii++;
                }
                x = c;
            }
            Console.WriteLine("\nМетодом бiсекцiї:\tx = {0:f5}\tІтерацiй: {1}", x, iteracii);
        }

        static void MethodHord(double a, double b, double e)
        {
            int iteracii = 0;
            double x;
            x = a - (b - a) / (Func(b) - Func(a)) * Func(a);
            while (Math.Abs(Func(x)) > e || (Math.Abs(x - a) > e && Math.Abs(x - b) > e))
            {
                if (Func(a) * Func2(a) > 0)
                {
                    b = x;
                    x = x - (Func(x) * (x - a) / (Func(x) - Func(a)));
                }
                else
                {
                    a = x;
                    x = x - (Func(x)) / (Func(b) - Func(x)) * (b - x);
                }
                iteracii++;
            }
            Console.WriteLine("Методом хорд:\t\tx = {0:f5}\tІтерацiй : {1}", x, iteracii);
        }

        static void MethodNewton(double a, double b, double e)
        {
            int iteracii = 1;
            double x, x0 = 0;
            if (Func(a) * Func2(a) > 0) x0 = a;
            else x0 = b;
            x = x0 - Func(x0) / Func1(x0);
            while (Math.Abs(x - x0) > e || Math.Abs(Func(x)) > e)
            {
                iteracii++;
                x0 = x;
                x = x0 - Func(x0) / Func1(x0);
            }
            Console.WriteLine("Методом Ньютона:\tx = {0:f5}\tІтерацiй : {1}", x, iteracii);
        }
    }
}
