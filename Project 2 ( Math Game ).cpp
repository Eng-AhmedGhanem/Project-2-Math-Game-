#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

string GetOpTypeSymbol(enOperationType OperationType)
{

	/*string arrOperationType[5] = { "+" , "-" , "x" , "/" ,"Mix" };
	return arrOperationType[OperationType - 1];*/

	switch (OperationType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

string GetQuestionLevelText(enQuestionLevel QuestinLevel)
{
	string Arr[4] = { "EasyLevel","MidLevel","HardLevel","Mix" };
	return Arr[QuestinLevel - 1];
}

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F"); // Green for correct answers.
	else
	{
		system("color 4F"); // Red for incorrect answers.
		cout << "\a"; // Plays an alert sound.
	}
}

short ReadHowManyQuestion()
{
	short NumberOfQuestions = 0;
	do
	{
		cout << "Enter How many question do you want to test Answer 1 To 10:  ";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;
}

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel = 0;
	do
	{
		cout << "Enter your Questions Level [1] Easy, [2] Mid, [3] Hard , [4] Mix : ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
	short OperationType = 0;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mult , [4] Div , [5] Mix : ";
		cin >> OperationType;

	} while (OperationType < 1 || OperationType > 5);

	return (enOperationType)OperationType;
}

struct stQuestion
{
	short Number1 = 0;
	short Number2 = 0;
	enOperationType OperationType;
	enQuestionLevel QuestionLevel;
	short CorrectAnswer;
	short PlayerAnswer;
	bool AnswerResult = true;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OperationType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool IsPass = true;
};

int SimpleCalculater(int Number1, int Number2, enOperationType OperationType)
{
	switch (OperationType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return  Number1 + Number2;
	}
}

stQuestion GenerateQuestion(enOperationType OperationType, enQuestionLevel QuestionLevel)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}

	if (OperationType == enOperationType::MixOp)
	{
		OperationType = (enOperationType)RandomNumber(1, 4);
	}

	Question.QuestionLevel = QuestionLevel;
	Question.OperationType = OperationType;	

	switch (QuestionLevel)	
	{
	case enQuestionLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationType);
		//Question.QuestionLevel = QuestionLevel;

		return Question;

	case enQuestionLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationType);
		//Question.QuestionLevel = QuestionLevel;

		return Question;
	case enQuestionLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OperationType);
		//Question.QuestionLevel = QuestionLevel;

		return Question;

	}
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.OperationType, Quizz.QuestionLevel);
	}
}

int ReadQuestionAnswer()
{
	int Answer;
	cin >> Answer;

	return Answer;
}

void PrintTheQuestions(stQuizz Quizz, short QuestionNumber)
{
	cout << "Question [ " << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n \n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n---------------" << endl;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;
		cout << "Wrong Answer :-( \n";
		cout << "The Right Answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
		cout << "=================" << endl;
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-)\n \n";
		cout << "=================" << endl;

	}

	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}



void AskAndCorrectQuestionsListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestions(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);

	}
	Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
	
	/*if (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers)
		Quizz.IsPass = true;
	else
		Quizz.IsPass = false;*/
}

string GetFinalResultText(bool True)
{
	if (True)
		return "Pass :-)";
	else
		return "Fail :-( ";
}

void PrintQuizzResult(stQuizz& Quizz)
{
	cout << "\n______________________________\n" << endl;;
	cout << " Final Results is " << GetFinalResultText(Quizz.IsPass) << endl;
	cout << "\n______________________________\n";
	cout << endl;
	cout << "Number OF Questions    : " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level         : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "Operatin Type          : " << GetOpTypeSymbol(Quizz.OperationType) << endl;
	cout << "Number Of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers: " << Quizz.NumberOfWrongAnswers;
	cout << "\n______________________________\n";
}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestion();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OperationType = ReadOpType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionsListAnswers(Quizz);
	PrintQuizzResult(Quizz);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PlayMathGame();

		cout << endl << "Do you want to Play Again (Y/N): ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();


	return 0;
}