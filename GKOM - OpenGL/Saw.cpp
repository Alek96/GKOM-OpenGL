#include "Saw.h"
#include "Cylinder.h"

Saw::Saw(int pieces, GLfloat width, GLfloat height, GLuint VAO, GLuint VBO)
{
	side = 0.0f;
	level = 0.0f;
	left = true;
	stop = true;
	up = false;
	number = pieces * 9 + 18;
	vao = VAO;
	vbo = VBO;
	tab = new GLfloat[number];
	// pierwszy trojkat
	tab[0] = tab[1] = tab[2] = 0.0f;
	tab[3] = 0.0f;
	tab[4] = height;
	tab[5] = 0.0f;
	tab[6] = width;
	tab[7] = height;
	tab[8] = 0.0f;

	//drugi trojkat
	tab[9] = tab[10] = tab[11] = 0.0f;
	tab[12] = width;
	tab[13] = tab[14] = 0.0f;
	tab[15] = width;
	tab[16] = height;
	tab[17] = 0.0f;

	// zeby pily
	GLfloat tooth = width / pieces;
	int j = 18;
	for (int i = 0; i < pieces; ++i)
	{

		tab[j] = tooth * i;
		tab[j + 1] = 0.0f;
		tab[j + 2] = 0.0f;

		tab[j + 3] = tooth * (i + 1);
		tab[j + 4] = 0.0f;
		tab[j + 5] = 0.0f;

		tab[j + 6] = (tab[j] + tab[j + 3]) / 2;
		tab[j + 7] = -0.1f;
		tab[j + 8] = 0.0f;
		j += 9;
	}

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, number * sizeof(GLfloat), tab, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);



}
Saw::~Saw()
{
	delete[] tab;
}
void Saw::draw(GLint modelLoc, GLint vertexColorLocation, Cylinder* log, GLfloat delta)
{
	glUniform4f(vertexColorLocation, 0.6f, 0.6f, 0.6f, 1.0f);
	glm::mat4 modelSaw;


	if (!stop)
	{
		if (!up)
		{
			if (side < -0.25f)
				left = false;
			else if (side > 0.25f)
				left = true;

			if (left)
				side = side - delta * 1.5f;
			else
				side = side + delta * 1.5f;

			if (level < 0.6f)
				level = level + delta * 0.2f;
			else
				up = true;
		}
		else
		{
			if (level < 0.0f)
			{
				up = false;
				stop = true;
				// uruchomienie ruszania drewna
				log->setStop(false);
				log->setMove(0.0f);
				int num = log->getLogNum();
				if (num < 3)
					log->setLogNum(num + 1);
			}
			else
				level = level - delta * 0.5f;
		}
	}

	modelSaw = glm::translate(modelSaw, glm::vec3(-2.925f + side, -1.75f - level, -1.5f));

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelSaw));
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, (number+1)/3);



}

void Saw::setStop(bool x)
{
	stop = x;
}

bool Saw::getStop()
{
	return stop;
}