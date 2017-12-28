#include "Cylinder.h"

Cylinder::Cylinder(GLfloat radius, int piecesNum, GLfloat height, GLuint VAO, GLuint VBO)
{
	move = 0.0f;
	stop = false;
	vao = VAO;
	vbo = VBO;
	pieces = piecesNum;
	logNum = 1;
	toDraw = (pieces * 36 + 1) / 3;
	int number = pieces * 36;
	tab = new GLfloat[number];

	int j = 0;
	for (int i = 0; i < pieces; ++i)
	{
		j = 36 * i;
		float u = 360.0f / pieces;
		float angle = glm::radians((float)i*u); 
		float angleNext = glm::radians((float)u*(i + 1)); 														
  // pierwsza podstawa
		tab[j] = 0.0f;
		tab[j + 1] = 0.0f;
		tab[j + 2] = 0.0f;

		tab[j + 3] = radius * cos(angle);
		tab[j + 4] = 0.0f;
		tab[j + 5] = radius * sin(angle);

		tab[j + 6] = radius * cos(angleNext);
		tab[j + 7] = 0.0f;
		tab[j + 8] = radius * sin(angleNext);
//pierwszy trojkat na scianie
		tab[j + 9] = radius * cos(angleNext);
		tab[j + 10] = 0.0f;
		tab[j + 11] = radius * sin(angleNext);

		tab[j + 12] = radius * cos(angle);
		tab[j + 13] = 0.0f;
		tab[j + 14] = radius * sin(angle);

		tab[j + 15] = radius * cos(angle);
		tab[j + 16] = -height;
		tab[j + 17] = radius * sin(angle);
	// drugi trojakt na scianie
		tab[j + 18] = radius * cos(angleNext);
		tab[j + 19] = -height;
		tab[j + 20] = radius * sin(angleNext);

		tab[j + 21] = radius * cos(angle);
		tab[j + 22] = -height;
		tab[j + 23] = radius * sin(angle);

		tab[j + 24] = radius * cos(angleNext);
		tab[j + 25] = 0.0f;
		tab[j + 26] = radius * sin(angleNext);
	// druga podstawa
		tab[j + 33] = 0.0f;
		tab[j + 34] = -height;
		tab[j + 35] = 0.0f;

		tab[j + 30] = radius * cos(angle);
		tab[j + 31] = -height;
		tab[j + 32] = radius * sin(angle);

		tab[j + 27] = radius * cos(angleNext);
		tab[j + 28] = -height;
		tab[j + 29] = radius * sin(angleNext);

	}
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 2 * number * sizeof(GLfloat), GL_NONE, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, number * sizeof(GLfloat) , tab);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

}
Cylinder::~Cylinder()
{
	delete[] tab;
}
void Cylinder::drawLog(GLint modelLoc, GLint vertexColorLocation, Saw* saw, GLfloat delta)
{
	if (!stop)
	{
		if (move < 3.5f)
			move = move + (1.5f * delta);
		else
		{
			stop = true;
			saw->setStop(false);
		}
	} 
	for (int i = 0; i < logNum; ++i)
	{
		
		glUniform4f(vertexColorLocation, 0.65f, 0.49f, 0.24f, 0.1f);
		glBindVertexArray(vao);
		if (i >= 1)
		{
			glm::mat4 modelWood;
			modelWood = translate(modelWood, glm::vec3(-2.0f, -2.25f, -4.0f + move + (i * 3.5f)));
			modelWood = glm::rotate(modelWood, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			modelWood = glm::scale(modelWood, glm::vec3(1.0f, 0.5f, 1.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelWood));
			glDrawArrays(GL_TRIANGLES, 0, toDraw);

			modelWood = glm::translate(modelWood, glm::vec3(0.0f, -2.15f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelWood));
			glDrawArrays(GL_TRIANGLES, 0, toDraw);
		}
		else
		{
			glm::mat4 modelWood;
			modelWood = translate(modelWood, glm::vec3(-2.0f, -2.25f, -4.0f + move + (i * 3.5f)));
			modelWood = glm::rotate(modelWood, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelWood));
			glDrawArrays(GL_TRIANGLES, 0, toDraw);
		}

		glBindVertexArray(0);
	}
}

void Cylinder::drawPillars(GLint modelLoc, GLint colorLoc, glm::vec3 *positions)
{
	
	glBindVertexArray(vao);
	for (int i = 0; i < 4; i++)
	{
		glm::mat4 model;
		model = translate(model, positions[i]);

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(colorLoc, 0.65f, 0.55f, 0.28f, 1.0f);

		glDrawArrays(GL_TRIANGLES, 0, toDraw);
		

	}
	glBindVertexArray(0);
}

void Cylinder::bindColor()
{
	int number = 36 * pieces;
	GLfloat* tabCol = new GLfloat[number];

	for (int i = 0; i < pieces; ++i)
	{
		tabCol[i * 36] = 0.75f;
		tabCol[i * 36 + 1] = 0.59f;
		tabCol[i * 36 + 2] = 0.34f;
		for (int j = 3; j < 31; j += 3)
		{
			tabCol[i * 36 + j] = 0.55f;
			tabCol[i * 36 + j + 1] = 0.39f;
			tabCol[i * 36 + j + 2] = 0.14f;
		}
		tabCol[i * 36 + 33] = 0.65f;
		tabCol[i * 36 + 34] = 0.49f;
		tabCol[i * 36 + 35] = 0.24f;
	}

	for (int i = 0; i < number / 2; ++i)
	{
		cout << "i: " << i << " tabCol: " << tabCol[i] << endl;
	}

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, number * sizeof(GLfloat), tabCol, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, number * sizeof(GLfloat), number * sizeof(GLfloat), tabCol);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(number * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	delete[] tabCol;

}

void Cylinder::setStop(bool x)
{
	stop = x;
}

void Cylinder::setMove(GLfloat x)
{
	move = x;
}

void Cylinder::setLogNum(int x)
{
	logNum = x;
}

int Cylinder::getLogNum()
{
	return logNum;
}

	void drawBasis(GLint modelLoc, GLuint VAO, GLint vertexColorLocation)
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-2.0f, -2.75f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 0.5f, 8.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glUniform4f(vertexColorLocation, 0.3f, 0.6f, 0.4f, 1.0f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);


	}

	void bindText(GLuint VAO, GLuint VBO, GLfloat* tab, int x)
	{
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER,  x * sizeof(GLfloat), tab, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0); 

	}

	void bind(GLuint VAO, GLuint VBO, GLfloat* floor, int x)
	{
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, x * sizeof(GLfloat), floor, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0); 
	}
