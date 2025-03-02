// Jeremy Hernandez
// ArithSeqTests.cs
// 1/14/2025

using NUnit.Framework;
using ArithSeq;

namespace ArithSeqTest
{

    [TestFixture]
    public class Tests
    {
        private ArithSeq.ArithSeq _arithSeq;

        [SetUp]
        public void Setup()
        {
            
            int firstTerm = 1;
            int difference = 2;
            int length = 10;
            int maxOperations = 30;
            
            _arithSeq = new ArithSeq.ArithSeq(firstTerm, difference, length, maxOperations);
        }

        [Test]
        public void Constructor_WillThrowArgumentException_InvalidSequenceLength()
        {
            // Arrange
            int firstTerm = 1;
            int invalidLength = -50;
            int length = 10;
            int maxOperations = 30;
            
            // Act & Assert
            var exception = Assert.Throws<ArgumentException>(() => new ArithSeq.ArithSeq(firstTerm, length, invalidLength, maxOperations));
            Assert.That(exception.Message, Does.Contain("Sequence length must be greater than or equal to 0"));
        }

        [Test]
        public void Constructor_WillThrowArgumentException_InvalidDifference()
        {
            // Arrange 
            int firstTerm = 1;
            int length = 5;
            int invalidDiff = -2;
            int maxOperations = 10;
            
            // Act & Assert
            var exception = Assert.Throws<ArgumentException>(() => new ArithSeq.ArithSeq(firstTerm, invalidDiff, length, maxOperations));
            Assert.That(exception.Message, Does.Contain("Difference must be greater than 0"));
        }
        
        [Test]
        public void GetKthTerm_WillReturnKthTerm_ValidInput()
        {
            // Arrange
            int firstTerm = 2;
            int length = 10;
            int difference = 2;
            int maxOperations = 30;
            
            // Act
            ArithSeq.ArithSeq seq = new ArithSeq.ArithSeq(firstTerm, difference, length, maxOperations);
            
            // Act & Assert
            Assert.That(seq.GetKthValue(5), Is.EqualTo(12));
            Assert.That(seq.GetKthValue(0), Is.EqualTo(2));
            Assert.That(seq.GetKthValue(1), Is.EqualTo(4));
            Assert.That(seq.GetKthValue(4), Is.EqualTo(10));
        }

        [Test]
        public void GetKthValue_WillThrowArgumentException_InvalidInput()
        {
            // Arrange
            int invalidKthValue = 11;
            
            // Act & Assert
            Assert.Throws<ArgumentException>(() => _arithSeq.GetKthValue(invalidKthValue));
        }

        [Test]
        public void DivisibleBy_WillThrowArgumentException_DivideByZero()
        {
            // Arrange
            int invalidDivisor = 0;
            
            // Act & Assert
            Assert.Throws<ArgumentException>(() => _arithSeq.DivisibleBy(invalidDivisor));
        }

        [Test]
        public void DivisibleBy_WillReturnCountOfDivisor_ValidInput()
        {
            // Arrange
            int firstTerm = 2;
            int length = 10;
            int difference = 1;
            int maxOperations = 30;
            
            // Act
            ArithSeq.ArithSeq seq = new ArithSeq.ArithSeq(firstTerm, difference, length, maxOperations);
            
            // Act & Assert
            Assert.That(seq.DivisibleBy(1), Is.EqualTo(10));
            Assert.That(seq.DivisibleBy(10), Is.EqualTo(1));
            Assert.That(seq.DivisibleBy(3), Is.EqualTo(3));
        }

        [Test]
        public void ModifySequence_ChangesSequenceOfQthTermByP_ValidInput()
        {
            // Arrange
            int firstTerm = 10;
            int length = 10;
            int difference = 10;
            int maxOperations = 40;

            int q = 100;
            int p = 2;
            
            // Act
            ArithSeq.ArithSeq seq = new ArithSeq.ArithSeq(firstTerm, difference, length, maxOperations);
            seq.ModifySequence(p, q);
            
            // Assert
            Assert.That(seq.GetSequence()[2], Is.EqualTo(130));
            Assert.That(seq.GetSequence()[4], Is.EqualTo(150));
            Assert.That(seq.GetSequence()[0], Is.EqualTo(10));
            Assert.That(seq.GetSequence()[9], Is.EqualTo(100));
        }

        [Test]
        public void ModifySequence_WillThrowArgumentException_InvalidSequenceLength()
        {
            // Arrange
            int firstTerm = 1;
            int length = 5;
            int difference = 3;
            int maxOperations = 30;

            int q = 2;
            int invalidSequenceLengthForP = -1;
            int outOfBoundValueForP = 6; 
            
            // Act
            ArithSeq.ArithSeq seq = new ArithSeq.ArithSeq(firstTerm, difference, length, maxOperations);
            
            // Assert
            Assert.Throws<ArgumentException>(() => seq.ModifySequence(invalidSequenceLengthForP, q));
            Assert.Throws<ArgumentException>(() => seq.ModifySequence(outOfBoundValueForP, q));
        }

        [Test]
        public void Reset_ReturnSequenceToOriginalSequence_ValidOutcome()
        {
            // Arrange
            int firstTerm = 1;
            int length = 10;
            int difference = 1;
            int maxOperations = 30;
            
            int q = 2;
            int p = 1;

            // Act
            ArithSeq.ArithSeq seq = new ArithSeq.ArithSeq(firstTerm, difference, length, maxOperations);
            
            // Assert
            Assert.That(seq.GetSequence()[1], Is.EqualTo(2));
            seq.ModifySequence(p, q);
            Assert.That(seq.GetSequence()[1], Is.EqualTo(4));
            
            seq.Reset();

            for (int i = 0; i < length; i++)
            {
                Assert.That(seq.GetSequence()[i], Is.EqualTo(i+1));
            }
        }
    }
}