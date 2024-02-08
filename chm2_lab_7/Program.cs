using System;

namespace chm2_lab_7
{
    class Program
    {
        static double Func(double x)
        {
            return Math.Log10(Math.Pow(x, 2) + 1) / x;
        }

        static double NewFunc(double x)
        {
            return 2 * (5 * Math.Log10(4 * Math.Pow(x, 2) + 24 * x + 61) - 10 * Math.Log10(5)) / (5 * (6 + 2 * x));
        }

        static double Simpson(Func<double, double> f, double a, double b, int n)
        {
            var h = (b - a) / n;
            var sum1 = 0d;
            var sum2 = 0d;
            for (var i = 1; i <= n; i++)
            {
                var xi = a + i * h;
                if (i <= n - 1) sum1 += f(xi);

                var xi_1 = a + (i - 1) * h;
                sum2 += f((xi + xi_1) / 2);
            }
            var result = h / 3d * (1d / 2d * f(a) + sum1 + 2 * sum2 + 1d / 2d * f(b));
            return result;
        }

        static double Gaus(double a, double b)
        {
            double x, rez = 0;
            double[] X = { -0.57735, 0.57735 };
            double[] A = { 1, 1 };
            for (int i = 0; i < 2; i++)
            {
                x = (a + b) / 2 + X[i] * (b - a) / 2;
                rez += A[i] * NewFunc(x);
            }
            return rez * (b - a) / 2;
        }

        static void Main(string[] args)
        {
            Console.OutputEncoding = System.Text.Encoding.Default;
            double a = 0.8, b = 1.6, e = 0.0001;

            //локальна функція
            double f(double x) => Math.Log10(Math.Pow(x, 2) + 1) / x;

            Console.WriteLine("ЛІМІТ:\n\nlg(x^2+1)\n----------\n    x\n\nвiд {0} до {1} з точнiстю до {2}\n\n", a, b, e);
            Console.WriteLine("МЕТОД СИМПСОНА:\n{0:f4}\n", Simpson(f, a, b, 8));
            Console.WriteLine("МЕТОД ГАУСА:\n{0:f4}", Gaus(-1, 1));
        }
    }
}
