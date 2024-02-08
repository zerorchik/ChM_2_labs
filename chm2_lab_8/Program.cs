using System;

namespace chm2_lab_8
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("y' = f(x,y)\nf(x,y) = y^2 + cos(y) / (2.2 + x), [0;2]");
            RungeKutte();
            Adams();
        }

        static double Function(double x, double y)
        {
            return Math.Pow(y, 2) + Math.Cos(y) / (2.2 + x);
        }

        static void RungeKutte()
        {
            double k1, k2, k3, k4, h = 0.1, e;
            int n = 300;
            double[] x = new double[n + 2];
            double[] y = new double[n + 2];
            int i = 0;
            Console.WriteLine("\nМЕТОД \"Рунге-Кутта\":");
            Console.WriteLine("x\ty\t\tПохибка");
            do
            {
                do
                {
                    x[i + 1] = x[i] + h;
                    k1 = Function(x[i], y[i]);
                    k2 = Function(x[i] + (h / 2), y[i] + (h * k1 / 2));
                    k3 = Function(x[i] + (h / 2), y[i] + (h * k2 / 2));
                    k4 = Function(x[i] + h, y[i] + (h * k3));
                    e = (Math.Pow(y[i], h) - Math.Pow(y[i], h / 2)) / (Math.Pow(2, 4) - 1);

                    if (Math.Abs((k2 - k3) / (k1 - k2)) > 0.09) h /= 2;
                } while (Math.Abs((k2 - k3) / (k1 - k2)) > 0.09);

                y[i + 1] = y[i] + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
                Console.WriteLine($"{x[i]:f1}\t{y[i]:f6}\t{e:f6}");
                i++;
            } while (x[i] < 2 + h);
        }
        static void Adams()
        {
            double k1, k2, k3, k4, h = 0.1, e, y_inter;
            int n = 100;
            double[] x = new double[n + 1];
            double[] y = new double[n + 1];
            Console.WriteLine("\nМЕТОД \"Адамса\":");

            Console.WriteLine("x\ty\t\tПохибка");
            int i = 0;
            do
            {
                do
                {
                    x[i + 1] = x[i] + h;
                    k1 = Function(x[i], y[i]);
                    k2 = Function(x[i] + (h / 2), y[i] + (h * k1 / 2));
                    k3 = Function(x[i] + (h / 2), y[i] + (h * k2 / 2));
                    k4 = Function(x[i] + h, y[i] + (h * k3));
                    e = (Math.Pow(y[i], h) - Math.Pow(y[i], h / 2)) / (Math.Pow(2, 4) - 1);

                    if (Math.Abs((k2 - k3) / (k1 - k2)) > 0.09) h /= 2;
                } while (Math.Abs((k2 - k3) / (k1 - k2)) > 0.09);
                Console.WriteLine($"{x[i]:f1}\t{y[i]:f6}\t{e:f6}");
                y[i + 1] = y[i] + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
                i++;
            } while (i < 3);
            h /= 2;
            int j = 3;
            do
            {
                do
                {
                    x[j + 1] = x[j] + h;
                    y[j + 1] = y[j] + (h / 24) * (55 * Function(x[j], y[j]) - 59 * Function(x[j - 1], y[j - 1]) + 37 * Function(x[j - 2], y[j - 2]) - 9 * Function(x[j - 3], y[j - 3]));
                    y_inter = y[j] + (h / 24) * (9 * Function(x[j + 1], y[j + 1]) + 19 * Function(x[j], y[j]) - 5 * Function(x[j - 1], y[j - 1]) + Function(x[j - 2], y[j - 2]));
                    if (Math.Abs(y_inter - y[j + 1]) > 0.09) h /= 2;
                }
                while (Math.Abs(y_inter - y[j + 1]) > 0.01);
                e = (Math.Pow(y[j], h) - Math.Pow(y[j], h / 2)) / (Math.Pow(2, 4) - 1);
                if (j % 2 != 0) Console.WriteLine($"{x[j]:f1}\t{y[j]:f6}\t{e:f6}");
                j++;
            }
            while (x[j] < 2 + h);
        }
    }
}
