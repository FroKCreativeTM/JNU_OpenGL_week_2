#include <iostream>
#include <glut.h>

#pragma warning(disable:4996)

void display()
{
	FILE* pFile;

	pFile = fopen("data.txt", "rt");

	// 캔버스 크기 300중
	// X, Y 각각 -150~150 즉 300을 전부 쓴다.
	int nX = 0, nY = 0;
	fscanf(pFile, "%d %d\n", &nX, &nY);
	printf("%d %d\n", nX, nY);

	// 컬러 버퍼 클리어
	glClear(GL_COLOR_BUFFER_BIT);

	// POINT(Pixel) 단위로 그린다.
	glBegin(GL_POINTS);

	// 재활용을 위해 변수명을 fColor로 시작하게 만들었다.
	float fBackRed, fBackGreen, fBackBlue;

	// 일단 백그라운드 컬러를 가져오자.
	fscanf(pFile, "%f %f %f\n\n", &fBackRed, &fBackGreen, &fBackBlue);
	printf("%.1f %.1f %.1f\n", fBackRed, fBackGreen, fBackBlue);

	// 삼각형 좌표와 컬러
	int px0, py0, pz0;											// p0
	int px1, py1, pz1;											// p1
	int px2, py2, pz2;											// p2
	float fTriangleRed, fTriangleGreen, fTriangleBlue;			// 삼각형 컬러

	// 삼각형 정보 받기
	fscanf(pFile, "%d %d %d %d %d %d %d %d %d %f %f %f\n",
		&px0, &py0, &pz0, &px1, &py1, &pz1, &px2, &py2, &pz2
		, &fTriangleRed, &fTriangleGreen, &fTriangleBlue);

	// 원 좌표와 컬러
	int rx, ry, rz;												// r
	int rad;													// radius
	float fCircleRed, fCircleGreen, fCircleBlue;				// 원의 컬러

	// 원 정보 받기
	fscanf(pFile, "%d %d %d %d %f %f %f\n",
		&rx, &ry, &rz, &rad, &fCircleRed, &fCircleGreen, &fCircleBlue);

	// 사각형의 좌표와 컬러
	int xMin, yMin, zMin;										// min
	int xMax, yMax, zMax;										// max
	float fQuadRed, fQuadGreen, fQuadBlue;				// 사각형의 컬러

	// 사각형 정보 받기
	fscanf(pFile, "%d %d %d %d %d %d %f %f %f\n",
		&xMin, &yMin, &zMin, &xMax, &yMax, &zMax, &fQuadRed, &fQuadGreen, &fQuadBlue);


	// 정보 표기(디버깅용)
	printf("%d %d %d %d %d %d %d %d %d %.1f %.1f %.1f\n",
		px0, py0, pz0, px1, py1, pz1, px2, py2, pz2
		, fTriangleRed, fTriangleGreen, fTriangleBlue);
	printf("%d %d %d %d %.1f %.1f %.1f\n",
		rx, ry, rz, rad, fCircleRed, fCircleGreen, fCircleBlue);
	printf("%d %d %d %d %d %d %.1f %.1f %.1f\n",
		xMin, yMin, zMin, xMax, yMax, zMax, fQuadRed, fQuadGreen, fQuadBlue);

	// 그리기
	for (int y = -nY; y <= nY; y++)
	{
		for (int x = -nX; x <= nX; x++)
		{
			// 삼각형 그리기
			// 다양한 방법이 있겠지만 저같은 경우엔
			// 직선의 방정식을 이용해서 그렸습니다.
			if ((y - py0 <= ((py0 - py1)/(px0 - px1)) * (x- px0))
				&& (y - py1 >= ((py1 - py2) / (px1 - px2)) * (x - px1))
				&& (y - py2 <= ((py2 - py0) / (px2 - px0)) * (x - px2)) )
			{
				glColor3f(fTriangleRed, fTriangleGreen, fTriangleBlue);
			}

			// 원 그리기 단 삼각형 뒤에 있단 걸 가정한다.
			// 원은 원의 방정식을 통해 처리한다.
			else if ( (rad * rad) >= ((x - rx) * (x - rx)) + ((y - ry) * (y - ry)))
			{
				glColor3f(fCircleRed, fCircleGreen, fCircleBlue);
			}

			// 사각형 그리기
			else if ((x >= xMin && y <= yMin) &&
				(x <= xMax && y >= yMax))
			{
				glColor3f(fQuadRed, fQuadGreen, fQuadBlue);
			}

			else
				glColor3f(fBackRed, fBackGreen, fBackBlue);

			glVertex2i(x, y);
		}
	}

	// POINT 그리기 끝
	glEnd();
	// 버퍼 비우기
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(300, 100);
	glutInitWindowSize(301, 301);
	glutCreateWindow("5 coloring");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150.0, 150.0, -150.0, 150.0, -1.0, 1.0);

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}