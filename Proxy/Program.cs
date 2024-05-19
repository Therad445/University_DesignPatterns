namespace Proxy;

using System;
using System.Drawing;
using System.Windows.Forms;

// Интерфейс для работы с изображением
interface IImage
{
    void Draw(Graphics g, Rectangle box);
    void LoadImage(string fileName);
}

// Реальное изображение
class RealImage : IImage
{
    private Image _image;

    public RealImage(string fileName)
    {
        LoadImage(fileName);
    }

    public void Draw(Graphics g, Rectangle box)
    {
        g.DrawImage(_image, box);
    }

    public void LoadImage(string fileName)
    {
        _image = Image.FromFile(fileName);
    }
}

// Прокси для изображения
class ImageProxy : IImage
{
    private string _fileName;
    private Image _image;
    private bool _imageLoaded = false; // Флаг для отслеживания загрузки изображения

    public ImageProxy(string fileName)
    {
        _fileName = fileName;
    }

    public void Draw(Graphics g, Rectangle box)
    {
        if (_imageLoaded)
        {
            g.DrawImage(_image, box);
        }
        else
        {
            using (Brush brush = new SolidBrush(Color.Black))
            {
                g.FillRectangle(brush, box);
            }
        }
    }

    public void LoadImage(string fileName)
    {
        _fileName = fileName;
        _image = Image.FromFile(fileName);
        _imageLoaded = true; // Устанавливаем флаг, чтобы показать, что изображение загружено
    }
}



// Форма для отображения и перемещения изображения
class MainForm : Form
{
    private Point _boxPosition = new Point(100, 100);
    private ImageProxy _imageProxy;

    public MainForm()
    {
        _imageProxy = new ImageProxy("TestImage.jpg");
        this.DoubleBuffered = true;
        this.Paint += MainForm_Paint;
        this.MouseDoubleClick += MainForm_MouseDoubleClick;
        this.MouseMove += MainForm_MouseMove;
    }

    private void MainForm_Paint(object sender, PaintEventArgs e)
    {
        Rectangle box = new Rectangle(_boxPosition.X, _boxPosition.Y, 100, 100);
        _imageProxy.Draw(e.Graphics, box);
    }

    private void MainForm_MouseDoubleClick(object sender, MouseEventArgs e)
    {
        if (e.Button == MouseButtons.Right)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Image Files (*.jpg, *.png, *.bmp)|*.jpg;*.png;*.bmp";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                _imageProxy.LoadImage(openFileDialog.FileName);
                this.Invalidate();
            }
        }
    }

    private void MainForm_MouseMove(object sender, MouseEventArgs e)
    {
        if (e.Button == MouseButtons.Left)
        {
            _boxPosition = e.Location;
            this.Invalidate();
        }
    }
}

// Входная точка приложения
class Program
{
    [STAThread]
    static void Main(string[] args)
    {
        Application.EnableVisualStyles();
        Application.SetCompatibleTextRenderingDefault(false);
        Application.Run(new MainForm());
    }
}

/*
 ----------------------       -----------------        ----------------       ----------------------
|        MainForm       |     |      IImage     |      |    RealImage   |     |    ImageProxy   |
 ----------------------       -----------------        ----------------       ----------------------
| - boxPosition: Point |     |                 |      | - _image: Image|     | - _realImage:    |
| - _imageProxy: IImage|---->|  + Draw()       |<-----|                |     |   RealImage      |
| + MainForm()         |     |  + LoadImage()  |      | + Draw()       |     | + LoadImage()    |
| + MainForm_Paint()   |     |                 |      | + LoadImage()  |     |                 |
| + MainForm_Mouse...()|     -----------------        ----------------       ----------------------
 ----------------------*/

// Добавить Proxy при пераом запуске